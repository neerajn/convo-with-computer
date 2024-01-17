/*
 * Client.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <vector>
#include "Message.h"

class Client
{
    public:

        ~Client ();

        bool start (char* port,  char* file);

        static Client& getInstance (void);
        static bool write(int fd, void* buf, unsigned int size);
        static bool read(int fd);

    private:

        Client ();
        int makeSocketNonBlocking (int sfd);
        int createClient (char* port);
        void err_show();

        static char* port_;
        static int socket_;
        static int ePolledFd_;

        static Client* instance_;
        static std::vector<MessageCommand*> jobs_;
};

#endif /* CLIENT_H_ */
