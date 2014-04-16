/**
 * A simple single file client
 *
 * TODO: Needs refactoring
 *
 */

#ifndef SIMPLECLIENT_H_
#define SIMPLECLIENT_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

#include "messaging.h"
#include "messagehandler.h"

class SimpleClient
{
    public:

        void start (char* ipaddress, int port)
        {
            int sock;
            struct sockaddr_in server;

            sock = socket (AF_INET, SOCK_STREAM, 0);

            if (sock == -1)
            {
                std::cout << "Client: create socket failed\n";

                exit (-1);
            }

            if (ipaddress == NULL)
            {
                std::cout << "Client: invalid server IP\n";
                exit (-1);
            }

            if (ipaddress == NULL)
            {
                std::cout << "Client: invalid server IP\n";
                exit (-1);
            }

            //TODO: more add IP Address and Port validation.

            server.sin_addr.s_addr = inet_addr(ipaddress);
            server.sin_family = AF_INET;
            server.sin_port = htons (port);

            int opt = -1;
            int rc = setsockopt (sock, IPPROTO_TCP, TCP_NODELAY, (char *)&opt, sizeof(opt));

            if (rc < 0)
            {
                perror ("Error disabling Nagle's algorithm");
                exit (-1);
            }

            //Connect to server
            if (connect (sock, (struct sockaddr *) &server , sizeof(server)) < 0)
            {
                perror("Connect failed");
                exit (-1);
            }

            std::cout << "Connected\n";

            //keep communicating with the server until 6 is selected
            while (1)
            {
                int64_t choice = 0;
                std::cout << "\nList of Services:\n";
                std::cout << "1. testprime\n";
                std::cout << "2. nextprime\n";
                std::cout << "3. nextnprimes\n";
                std::cout << "4. getdate\n";
                std::cout << "5. filetestoperation\n";
                std::cout << "6. exit\n";
                std::cout << "\nEnter your choice : ";
                std::cin >> choice;

                if (choice > 6)
                {
                    std::cout << "Invalid choice.\n";
                    continue;
                }

                if (choice < 1)
                {
                    std::cout << "Invalid choice.\n";
                    continue;
                }

                MessageHandler messagehandler;

                switch (choice)
                {
                    case 1:
                    {
                        int number = 0;
                        std::cout << "Enter prime number: \n";
                        std::cin >> number;

                        if (number < 1)
                        {
                            std::cout << "Invalid input\n";
                            break;
                        }

                        RequestHeader header;
                        header.m_msgType = TESTPRIME;
                        RequestTestPrime testprimerequest;
                        testprimerequest.m_number = number;

                        //std::cout << "Sending Request header\n";

                        // two write can be combined to one later
                        if (!this->write (sock, (void*)&header, sizeof (RequestHeader)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        //std::cout << "Sending Request header " << (int) header.m_msgType << std::endl;


                        if (!this->write (sock, (void*)&testprimerequest, sizeof (RequestTestPrime)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        //std::cout << "Sending Request " << (int) testprimerequest.m_number << std::endl;

                        ResponseHeader rheader;
                        //Receive a reply from the server
                        if (!this->read (sock, (void*)&rheader, sizeof (ResponseHeader)))
                        {
                            std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        //std::cout << "Processing header " << (int)rheader.m_msgType << std::endl;

                        messagehandler.process (rheader);

                        if (rheader.m_msgType == RESPONSE_ERROR)
                        {
                            std::cout << "Error message received from the server: \n";

                            ResponseError errorresponse;

                            //std::cout << "Reading response header\n";

                            //Receive a reply from the server
                            if (!this->read (sock, (void*)&errorresponse, sizeof (ResponseError)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }
                            //std::cout << "Processing response \n";
                            messagehandler.processResponse ((char*)&errorresponse, sizeof (ResponseError));
                        }
                        else
                        {
                            ResponseTestPrime testprimeresponse;

                            //std::cout << "Reading response\n";

                            //Receive a reply from the server
                            if (!this->read (sock, (void*)&testprimeresponse, sizeof (ResponseTestPrime)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }

                            //std::cout << "Processing response \n";
                            messagehandler.processResponse ((char*)&testprimeresponse, sizeof (ResponseTestPrime));
                        }

                        break;
                    }
                    case 2:
                    {
                        int number = 0;
                        std::cout << "Enter a number: \n";
                        std::cin >> number;

                        if (number < 1)
                        {
                            std::cout << "Invalid input\n";
                            break;
                        }

                        RequestHeader header;
                        header.m_msgType = NEXTPRIME;
                        RequestNextPrime nextprimerequest;
                        nextprimerequest.m_number = number;

                        // two write can be combined to one later
                        if (!this->write (sock, (char*)&header, sizeof (RequestHeader)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }
                        if (!this->write (sock, (char*)&nextprimerequest, sizeof (RequestNextPrime)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        ResponseHeader rheader;
                        //Receive a reply from the server
                        if (!this->read (sock, (char*)&rheader, sizeof (ResponseHeader)))
                        {
                            std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        messagehandler.process (rheader);

                        if (rheader.m_msgType == RESPONSE_ERROR)
                        {
                            std::cout << "Error message received from the server: \n";

                            ResponseError errorresponse;

                            //Receive a reply from the server
                            if (!this->read (sock, (char*)&errorresponse, sizeof (ResponseError)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }

                            messagehandler.processResponse ((char*)&errorresponse, sizeof (ResponseError));
                        }
                        else
                        {
                            ResponseNextPrime nextprimeresponse;

                            //Receive a reply from the server
                            if (!this->read (sock, (char*)&nextprimeresponse, sizeof (ResponseNextPrime)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }

                            messagehandler.processResponse ((char*)&nextprimeresponse, sizeof (ResponseNextPrime));
                        }
                        break;
                    }
                    case 3:
                    {
                        int number = 0;
                        std::cout << "Enter a number: \n";
                        std::cin >> number;

                        if (number < 1)
                        {
                            std::cout << "Invalid input\n";
                            break;
                        }

                        int rangenumber = 0;
                        std::cout << "Enter a range number: \n";
                        std::cin >> rangenumber;

                        if (rangenumber < 1 || rangenumber <= number)
                        {
                            std::cout << "Invalid input\n";
                            break;
                        }

                        RequestHeader header;
                        header.m_msgType = NEXTNPRIMES;
                        RequestNextNPrimes nextnprimerequest;
                        nextnprimerequest.m_number = number;
                        nextnprimerequest.m_howMany = rangenumber;

                        // two write can be combined to one later
                        if (!this->write (sock, (char*)&header, sizeof (RequestHeader)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }
                        if (!this->write (sock, (char*)&nextnprimerequest, sizeof (RequestNextNPrimes)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        ResponseHeader rheader;
                        //Receive a reply from the server
                        if (!this->read (sock, (char*)&rheader, sizeof (ResponseHeader)))
                        {
                            std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        messagehandler.process (rheader);

                        if (rheader.m_msgType == RESPONSE_ERROR)
                        {
                            std::cout << "Error message received from the server: \n";

                            ResponseError errorresponse;

                            //Receive a reply from the server
                            if (!this->read (sock, (char*)&errorresponse, sizeof (ResponseError)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }

                            messagehandler.processResponse ((char*)&errorresponse, sizeof (ResponseError));
                        }
                        else
                        {
                            ResponseNextNPrime nextnprimeresponse;

                            //Receive a reply from the server
                            if (!this->read (sock, (char*)&nextnprimeresponse, sizeof (ResponseNextNPrime)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }

                            messagehandler.processResponse ((char*)&nextnprimeresponse, sizeof (ResponseNextNPrime));
                        }

                        break;
                    }
                    case 4:
                    {
                        RequestHeader header;
                        header.m_msgType = GETDATE;
                        RequestGetDate getdaterequest;

                        // two write can be combined to one later
                        if (!this->write (sock, (void*)&header, sizeof (RequestHeader)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }
                        if (!this->write (sock, (void*)&getdaterequest, sizeof (RequestGetDate)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        ResponseHeader rheader;
                        //Receive a reply from the server
                        if (!this->read (sock, (void*)&rheader, sizeof (ResponseHeader)))
                        {
                            std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        messagehandler.process (rheader);
                        //std::cout << (int)rheader.m_msgType << std::endl;

                        if (rheader.m_msgType == RESPONSE_ERROR)
                        {
                            std::cout << "Error message received from the server: \n";

                            ResponseError errorresponse;

                            //Receive a reply from the server
                            if (!this->read (sock, (void*)&errorresponse, sizeof (ResponseError)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }

                            messagehandler.processResponse ((char*)&errorresponse, sizeof (ResponseError));
                        }
                        else
                        {
                            ResponseGetDate getdateresponse;

                            //Receive a reply from the server
                            if (!this->read (sock, (void*)&getdateresponse, sizeof (ResponseGetDate)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }

                            messagehandler.processResponse ((char*)&getdateresponse, sizeof (ResponseGetDate));
                        }
                        break;
                    }
                    case 5:
                    {
                        std::string filepath;
                        std::cout << "Enter fully qualified file name: \n";
                        std::cin >> filepath;

                        if (filepath == "")
                        {
                            std::cout << "Invalid input\n";
                            break;
                        }

                        if (filepath.size() > (MAX_FILE_PATH_NAME_SIZE - 1))
                        {
                            std::cout << "Unsupported file name length\n";
                            break;
                        }

                        RequestHeader header;
                        header.m_msgType = FILETESTOPERATION;
                        RequestFileTestOperation filetestoperationrequest;
                        strcpy (filetestoperationrequest.m_filepathname, filepath.c_str());

                        // two write can be combined to one later
                        if (!this->write (sock, (char*)&header, sizeof (RequestHeader)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }
                        if (!this->write (sock, (char*)&filetestoperationrequest, sizeof (RequestFileTestOperation)))
                        {
                            std::cout << "Send to server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        ResponseHeader rheader;
                        //Receive a reply from the server
                        if (!this->read (sock, (char*)&rheader, sizeof (ResponseHeader)))
                        {
                            std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            exit (1);
                        }

                        messagehandler.process (rheader);

                        if (rheader.m_msgType == RESPONSE_ERROR)
                        {
                            std::cout << "Error message received from the server: \n";

                            ResponseError errorresponse;

                            //Receive a reply from the server
                            if (!this->read (sock, (char*)&errorresponse, sizeof (ResponseError)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }

                            messagehandler.processResponse ((char*)&errorresponse, sizeof (ResponseError));
                        }
                        else
                        {
                            ResponseFileTestOperation filetestoperationresponse;

                            //Receive a reply from the server
                            if (!this->read (sock, (char*)&filetestoperationresponse, sizeof (ResponseFileTestOperation)))
                            {
                                std::cout << "Receive data from server failed. Unable to service requests. Exiting.\n";
                            }

                            messagehandler.processResponse ((char*)&filetestoperationresponse, sizeof (ResponseFileTestOperation));
                        }
                        break;
                    }
                    case 6:
                    {
                        close (sock);
                        exit (1);
                        break;
                    }
                    default:
                    {
                        close (sock);
                        exit (1);
                        break;
                    }
                }
            }

            close(sock);
        }

    private:

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
            //std::cout << "Bytes to read: " << readsize << std::endl;

            while (1)
            {

                int rc = ::recv (fd, (char*)buf + count, readsize - count, MSG_DONTWAIT);

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
            //std::cout << "Bytes to write: " << writesize << std::endl;

            while (1)
            {
                int rc = ::send (fd, (char*)buf + count, writesize - count, MSG_DONTWAIT);

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

};

#endif
