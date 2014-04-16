#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <atomic>
#include <string.h>
#include <unistd.h>

#include "messaging.h"
#include "messagehandler.h"

class Server
{
    public:
        
        Server ()
        {
            m_listenSocket = 0;
            m_maxSockets = 0;
            m_stopServer = false;

            memset ((void*)&m_masterSet, 0, sizeof (struct fd_set));
            memset ((void*)&m_workingSet, 0, sizeof (struct fd_set));
        }
        
        ~Server ()
        {
            cleanUp ();
        }

        void startEngine (char* ipaddress, int port)
        {
            int    len;
            int    rc;
            int    newSocket;
            int    descriptorReady;
            bool   closeConnection = false;
            struct timeval       timeout;

            startListen (port);
           
            timeout.tv_sec  = 0;
            timeout.tv_usec = 0;

            // main loop
            do
            {
                memcpy (&m_workingSet, &m_masterSet, sizeof(m_masterSet));

                rc = select (m_maxSockets + 1, &m_workingSet, NULL, NULL, &timeout);

                if (rc < 0)
                {
                    perror("select failed");
                    break;
                }
        /*
                if (rc == 0)
                {
                    printf("  select() timed out.  End program.\n");
                    break;
                }
        */
                descriptorReady = rc;

                for (int i = 0; i <= m_maxSockets  &&  descriptorReady > 0; ++i)
                {
                    if (FD_ISSET (i, &m_workingSet))
                    {
                        descriptorReady -= 1;

                        if (i == m_listenSocket)
                        {
                            do
                            {
                                newSocket = accept (m_listenSocket, NULL, NULL);

                                if (newSocket < 0)
                                {
                                    if (errno != EWOULDBLOCK)
                                    {
                                        perror ("accept failed for a client");
                                    }
                                    break;
                                }

                                // a new client
                                FD_SET (newSocket, &m_masterSet);

                                if (newSocket > m_maxSockets)
                                {
                                    m_maxSockets = newSocket;
                                }

                            } while (newSocket != -1);
                        }
                        else
                        {
                            closeConnection = false;

                            do
                            {
                                RequestHeader header;
                                rc = recv (i, (char*)&header, sizeof(RequestHeader), 0);

                                if (rc < 0)
                                {
                                    if (errno != EWOULDBLOCK)
                                    {
                                        perror ("recv header failed");
                                        closeConnection = true;
                                    }
                                    break;
                                }

                                if (rc == 0)
                                {
                                    closeConnection = true;
                                    break;
                                }

                                MessageHandler messagehandler;

                                int bodylength = messagehandler.process (header);

                                char buffer[bodylength];
                                memset (buffer, 0, sizeof(char) * bodylength);

                                rc = recv (i, buffer, sizeof(char) * bodylength, 0);

                                if (rc < 0)
                                {
                                    if (errno != EWOULDBLOCK)
                                    {
                                        perror ("recv body failed");
                                        closeConnection = true;
                                    }
                                    break;
                                }

                                if (rc == 0)
                                {
                                    closeConnection = true;
                                    break;
                                }

                                char* returnBuffer = NULL;

                                char returnErrorBuffer [sizeof(ResponseHeader) + sizeof(ResponseError)];
                                ResponseHeader* responseheader = returnErrorBuffer;
                                ResponseError* error = returnErrorBuffer + sizeof(ResponseHeader);

                                int returnbuffersize = messagehandler.process (buffer, bodylength, returnBuffer);

                                if (returnbuffersize <= 0 || returnBuffer == NULL)
                                {
                                    responseheader->m_msgType = ERROR;

                                    error->m_errorCode = ERROR;
                                    strcpy (error->m_errorMsg, "Server cannot process your request.");

                                    returnBuffer = (char*)returnErrorBuffer;
                                    returnbuffersize = sizeof(ResponseHeader) + sizeof(ResponseError);
                                }

                                rc = send (i, returnBuffer, returnbuffersize, 0);

                                if (rc < 0)
                                {
                                    perror ("send failed");
                                    closeConnection = true;
                                    break;
                                }
                                
                            } while (true);

                            if (closeConnection)
                            {
                                close (i);
                                FD_CLR (i, &m_masterSet);
                    
                                if (i == m_maxSockets)
                                {
                                    while (FD_ISSET (m_maxSockets, &m_masterSet) == false)
                                    {
                                        m_maxSockets -= 1;
                                    }
                                }
                            }
                        }
                    }
                }
            } while (m_stopServer == false);
        }
        
        void stopServer ()
        {
            m_stopServer = true;
        }
        
    private:

        void startListen (int port)
        {
            struct sockaddr_in   addr;
            int rc = 0;

            // create a listen socket
            m_listenSocket = socket (AF_INET, SOCK_STREAM, 0);

            // if create socket fails then no point continuing
            if (m_listenSocket < 0)
            {
                perror ("socket failed");
                exit (-1);
            }

            setSocketOptions ();

            memset (&addr, 0, sizeof (addr));
            addr.sin_family      = AF_INET;
            addr.sin_addr.s_addr = htonl (INADDR_ANY);
            addr.sin_port        = htons (port);

            rc = bind (m_listenSocket, (struct sockaddr *)&addr, sizeof(addr));

            if (rc < 0)
            {
                perror ("bind failed");
                close (m_listenSocket);
                exit (-1);
            }

            // queue up 1024 client. can be a config entry
            rc = listen (m_listenSocket, 1024);
            if (rc < 0)
            {
                perror ("listen failed");
                close (m_listenSocket);
                exit (-1);
            }

            FD_ZERO (&m_masterSet);
            m_maxSockets = m_listenSocket;
            FD_SET (m_listenSocket, &m_masterSet);
        }

        void setSocketOptions ()
        {
            int rc = 0;
            int on = 1;
            // let the socket descriptor be reuseable
            rc = setsockopt (m_listenSocket, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on));

            // if setsocketopt fails then no point continuing
            if (rc < 0)
            {
                perror ("setsockopt failed");
                close (m_listenSocket);
                exit (-1);
            }

            // set socket to be non blocking
            rc = ioctl (m_listenSocket, FIONBIO, (char *)&on);

            if (rc < 0)
            {
                perror ("ioctl failed");
                close (m_listenSocket);
                exit (-1);
            }
        }

        void cleanUp ()
        {
            for (int i = 0; i <= m_maxSockets; ++i)
            {
                if (FD_ISSET (i, &m_masterSet))
                {
                    close(i);
                }
            }
        }
        
    private:
        
        int m_listenSocket;
        int m_maxSockets;
        std::atomic<bool> m_stopServer;
        struct fd_set m_masterSet;
        struct fd_set m_workingSet;
    
};
