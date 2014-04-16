/**
 * A server functionality is handled here.
 *
 * TODO: Needs refactoring
 *
 */
#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/tcp.h>

#include "services.h"
#include "messaging.h"
#include "messagehandler.h"

#define A_LARGE_BUFFER 65535

class Server
{
    public:
        
        Server ()
        {
            m_listenSocket = 0;
            m_maxSockets = 0;

            memset ((void*)&m_masterSet, 0, sizeof (fd_set));
            memset ((void*)&m_workingSet, 0, sizeof (fd_set));
        }
        
        ~Server ()
        {
            cleanUp ();
        }

        void startEngine (int port)
        {
            int    rc;
            int    newSocket;
            int    descriptorReady;
            struct timeval       timeout;

            // get ready to listen for incoming connections and start listening
            startListen (port);
           
            timeout.tv_sec  = 0;
            timeout.tv_usec = 0;

            // main loop
            do
            {
                memcpy ((void*)&m_workingSet, (void*)&m_masterSet, sizeof(m_masterSet));

                rc = select (m_maxSockets + 1, (fd_set*)&m_workingSet, NULL, NULL, &timeout);

                if (rc < 0)
                {
                    perror("select failed");
                    break;
                }

                descriptorReady = rc;

                for (int i = 0; i <= m_maxSockets  &&  descriptorReady > 0; ++i)
                {
                    if (FD_ISSET (i, (fd_set*)&m_workingSet))
                    {
                        descriptorReady -= 1;

                        // we need to accept a new client
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
                                FD_SET (newSocket, (fd_set*)&m_masterSet);

                                if (newSocket > m_maxSockets)
                                {
                                    m_maxSockets = newSocket;
                                }

                            } while (newSocket != -1);
                        }
                        else
                        {
                            // a client has sent a request; handle it.
                            //do
                            //{
                                // ALGO:
                                // As per protocol, read the request header
                                // let the message handler process the header
                                // then read the request body
                                // let the message handle process the body
                                // send back the result to the client
                                // if we notice the error in between recving or sending
                                // close the connection

                                //std::cout << "Read request\n";

                                RequestHeader header;
                                bool readheaderret = this->read (i, (char*)&header, sizeof(RequestHeader));

                                if (!readheaderret)
                                {
                                    close (i);
                                    FD_CLR (i, (fd_set*)&m_masterSet);

                                    if (i == m_maxSockets)
                                    {
                                        while (FD_ISSET (m_maxSockets, (fd_set*)&m_masterSet) == false)
                                        {
                                            m_maxSockets -= 1;
                                        }
                                    }
                                }

                                // process the header
                                MessageHandler messagehandler;
                                int bodylength = messagehandler.process (header);

                                // read the message body
                                char buffer[bodylength];
                                memset (buffer, 0, sizeof(char) * bodylength);
                                bool readret = this->read (i, buffer, sizeof(char) * bodylength);

                                if (!readret)
                                {
                                    close (i);
                                    FD_CLR (i, (fd_set*)&m_masterSet);

                                    if (i == m_maxSockets)
                                    {
                                        while (FD_ISSET (m_maxSockets, (fd_set*)&m_masterSet) == false)
                                        {
                                            m_maxSockets -= 1;
                                        }
                                    }
                                }

                                memset ((void*)m_returnBuffer, 0, A_LARGE_BUFFER);
                                uint16_t returnBufferSize = 0;

                                std::cout << "Processing message\n";

                                // in case of error
                                messagehandler.process (buffer, bodylength, m_returnBuffer, returnBufferSize);

                                //std::cout << "Write response header and response: " << (int)((ResponseHeader*)m_returnBuffer)->m_msgType << std::endl;

                                // write back the result.
                                bool sendresult = this->write (i, (void*)m_returnBuffer, (unsigned int)returnBufferSize);

                                if (!sendresult)
                                {
                                    close (i);
                                    FD_CLR (i, (fd_set*)&m_masterSet);

                                    if (i == m_maxSockets)
                                    {
                                        while (FD_ISSET (m_maxSockets, (fd_set*)&m_masterSet) == false)
                                        {
                                            m_maxSockets -= 1;
                                        }
                                    }
                                }
                                
                                std::cout << "done\n";

                            //} while (true);

                        }
                    }
                }
            } while (1);
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

            FD_ZERO ((fd_set*)&m_masterSet);
            m_maxSockets = m_listenSocket;
            FD_SET (m_listenSocket, (fd_set*)&m_masterSet);
        }

        void setSocketOptions ()
        {
            int rc = 0;
            int on = 1;
            // let the socket descriptor be reuseable
            rc = setsockopt (m_listenSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

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

            int opt = -1;
            rc = setsockopt (m_listenSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&opt, sizeof(opt));

            if (rc < 0)
            {
                perror ("Error disabling Nagle's algorithm");
                close (m_listenSocket);
                exit (-1);
            }
        }

        void cleanUp ()
        {
            for (int i = 0; i <= m_maxSockets; ++i)
            {
                if (FD_ISSET (i, (fd_set*)&m_masterSet))
                {
                    close(i);
                }
            }
        }
        
        void err_show()
        {
            if(EBADF == errno)
            {
                std::cout << "error  is EBADF" << std::endl;
            }
            else if(EEXIST == errno)
            {
                std::cout << "error  is EEXIST" << std::endl;
            }
            else if(EINVAL == errno)
            {
                std::cout << "error  is EINVAL" << std::endl;
            }
            else if(ENOENT == errno)
            {
                std::cout << "error  is ENOENT" << std::endl;
            }
            else if(ENOMEM == errno)
            {
                std::cout << "error  is ENOMEM" << std::endl;
            }
            else if(ENOSPC == errno)
            {
                std::cout << "error  is ENOSPC" << std::endl;
            }
            else if(EAGAIN == errno)
            {
                std::cout << "error  is EAGAIN" << std::endl;
            }
            else if(EWOULDBLOCK == errno)
            {
                std::cout << "error  is EWOULDBLOCK" << std::endl;
            }
        }

        bool read(int fd, void* buf, unsigned int readsize)
        {
            uint32_t count = 0;
            std::cout << "Bytes to read: " << readsize << std::endl;

            while (1)
            {

                int rc = ::recv (fd, (char*)buf + count, readsize - count, 0);

                if (rc < 0)
                {
                    if (errno != EWOULDBLOCK)
                    {
                        err_show();
                        perror ("recv body failed");
                        return false;
                    }
                }
                else if (rc == 0) //orderly disconnect by client
                {
                    return false;
                }
                else if ((uint32_t)rc == readsize) // full read
                {
                    return true;
                }
                else //partial read
                {
                    count += (uint32_t)rc;

                    if (count == readsize)
                    {
                        return true;
                    }
                }
            }

            return true;
        }

        bool write(int fd, void* buf, unsigned int writesize)
        {
            uint32_t count = 0;
            std::cout << "Bytes to write: " << writesize << std::endl;

            while (1)
            {
                int rc = ::send (fd, (char*)buf + count, writesize - count, 0);

                if (rc < 0)
                {
                    if (errno != EWOULDBLOCK)
                    {
                        err_show();
                        perror ("send body failed");
                        return false;
                    }
                }
                else if (rc == 0) //orderly disconnect by client
                {
                    return false;
                }
                else if ((uint32_t)rc == writesize) // full write
                {
                    return true;
                }
                else //partial write
                {
                    count += (uint32_t)rc;

                    if (count == writesize)
                    {
                        return true;
                    }
                }
            }

            return true;
        }

    private:
        
        int m_listenSocket;
        int m_maxSockets;
        fd_set m_masterSet;
        fd_set m_workingSet;

        char m_returnBuffer [A_LARGE_BUFFER];
    
};

#endif
