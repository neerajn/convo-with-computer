/*
 * Connection.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "JobWorker.h"

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
#include <pthread.h>

class Connection
{
    public:

        ~Connection ();

        bool start (char* port);

        static Connection& getInstance (void);
        bool write(int fd, void* buf, unsigned int size);
        bool read(int fd, void* buf, unsigned int size);

    private:

        Connection ();
        int makeSocketNonBlocking (int sfd);
        int createServer (char* port);
        void err_show();
        bool accept(struct epoll_event* events, struct epoll_event& event);

        char* port_;
        int listenSocket_;
        int ePolledFd_;
        pthread_mutex_t readMutex_;
        pthread_mutex_t writeMutex_;

        static Connection* instance_;
};

#endif /* CONNECTION_H_ */
