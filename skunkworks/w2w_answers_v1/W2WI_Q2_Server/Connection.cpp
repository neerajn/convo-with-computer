/*
 * Connection.cpp
 *
 *  Created on: Apr 14, 2013Socket::Connection ()
 *      Author: neeraj
 */
#include <iostream>
#include "Connection.h"
#include "Message.h"
#include "Command.h"
#include "CommandData.h"
#include "MultCommand.h"
#include "AddCommand.h"
#include "SubtractCommand.h"
#include "PowCommand.h"
#include "XorCommand.h"
#include "ClientData.h"

#define MAXEVENTS 64

Connection* Connection::instance_ = NULL;

Connection::Connection ():
                port_ (NULL),
                listenSocket_ (0),
                ePolledFd_ (0)
{
    // TODO Auto-generated constructor stub
    readMutex_ = PTHREAD_MUTEX_INITIALIZER;
    writeMutex_ = PTHREAD_MUTEX_INITIALIZER;
}

Connection::~Connection ()
{
    // TODO Auto-generated destructor stub
}

Connection& Connection::getInstance (void)
{
    if (NULL == instance_)
    {
        instance_ = new Connection();
    }

    return *instance_;
}

int Connection::makeSocketNonBlocking (int sfd)
{
    int flags, s;

    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1)
    {
        perror ("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags);

    if (s == -1)
    {
        perror ("fcntl");
        return -1;
    }

    return 0;
}

int Connection::createServer (char* port)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;

    memset (&hints, 0, sizeof (struct addrinfo));

    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC;     // Return IPv4 and IPv6 choices
    hints.ai_socktype = SOCK_STREAM; // We want a TCP socket
    hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;     // All interfaces

    s = getaddrinfo (NULL, port, &hints, &result);

    if (s != 0)
    {
        perror("getaddrinfo");
        std::cout << "getaddrinfo failed" << std::endl;
        return -1;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (sfd == -1)
        {
            err_show();
            std::cout << "socket failed" << std::endl;
            continue;
        }
        int optval = 1;
        if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
        {
            perror("setsockopt");
            return -1;
        }

        s = bind (sfd, rp->ai_addr, rp->ai_addrlen);

        if (s == 0)
        {
            // We managed to bind successfully
            break;
        }
        else
        {
            std::cout << "bind failed" << std::endl;
        }

        close(sfd);
    }

    if (rp == NULL)
    {
        err_show();
        fprintf (stderr, "Could not bind\n");
        return -1;
    }

    freeaddrinfo (result);

    return sfd;
}

bool Connection::start(char* port)
{
    int s;
    struct epoll_event  event;
    struct epoll_event* events;

    listenSocket_ = createServer (port);

    if (listenSocket_ == -1)
    {
        err_show();
        std::cout << "create failed" << std::endl;
        return false;
    }

    s = makeSocketNonBlocking (listenSocket_);

    if (s == -1)
    {
        err_show();
        std::cout << "makeSocketNonBlocking failed" << std::endl;
        return false;
    }

    s = listen (listenSocket_, SOMAXCONN);

    if (s == -1)
    {
        perror("listen");
        return false;
    }

    ePolledFd_ = epoll_create1 (0);

    if (ePolledFd_ == -1)
    {
        perror("epoll_create");
        return false;
    }

    event.events = EPOLLIN | EPOLLET | EPOLLOUT;
    event.data.fd = listenSocket_;
    s = epoll_ctl (ePolledFd_, EPOLL_CTL_ADD, listenSocket_, &event);

    if (s == -1)
    {
        perror("epoll_ctl");
        return false;
    }

    // Buffer where events are returned
    events = (epoll_event*)calloc (MAXEVENTS, sizeof(event));
    int errsv = errno;
    if (events == NULL)
    {
        std::cout << "calloc failed:" << strerror(errsv) << std::endl;
    }

    // The event loop
    while (1)
    {
        int n, i;

        do
        {
            n = epoll_wait (ePolledFd_, events, MAXEVENTS, -1);
            err_show();
        } while (n < 0 && errno == EINTR);

        for (i = 0; i < n; i++)
        {
            int fdd = events[i].data.fd;

            if (listenSocket_ == fdd)
            {
                // We have a notification on the listening socket, which
                // means one or more incoming connections.
                accept(events, event);

            }
            else if(events[i].events & EPOLLIN)
            {
                // We have data on the fd waiting to be read. Read and
                // display it. We must read whatever data is available
                // completely, as we are running in edge-triggered mode
                // and won't get a notification again for the same
                // data.
                std::cout << "start: read client socket" << fdd << std::endl;

                Job* job = new Job();
                job->setJobState(READ);

                ClientData* clientdata = new ClientData();
                clientdata->setFileDescriptor(fdd);

                JobWorkerContext* jobC = new JobWorkerContext();
                jobC->setJob(job);
                jobC->setConnection(this);
                jobC->setClientData(clientdata);

                JobWorker::addWork (jobC);
            }
            else if(events[i].events & EPOLLOUT)
            {
                //std::cout << "start: write client socket" << fdd << std::endl;
                //int done = read(fdd);
            }
            else if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (events[i].events & EPOLLRDHUP) ||
                ((events[i].events & EPOLLIN)!= EPOLLIN &&
                (events[i].events & EPOLLOUT) != EPOLLOUT))
            {
                // An error has occured on this fd, or the socket is not
                // ready for reading (why were we notified then?)
                err_show();
                std::cout << "closing connection" << std::endl;
                fprintf (stderr, "epoll error\n");
                close (fdd);
            }
        }
    }

    free (events);
    close (listenSocket_);
}

void Connection::err_show()
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

bool Connection::read(int fd, void* buf, unsigned int readsize)
{
    ssize_t count = 0;
    int errsv = 0;

    while (1)
    {
        pthread_mutex_lock (&readMutex_);

        count = ::recv (fd, buf + count, readsize - count, MSG_DONTWAIT);
        errsv = errno;

        pthread_mutex_unlock (&readMutex_);

        std::cout << "Read bytes" << count << std::endl;

        if (count == -1)
        {
            printf("%s: %s\n","recv", strerror(errsv));
            // If errno == EAGAIN, that means we have read all
            //   data. So go back to the main loop.
            if (errsv != EAGAIN || errsv != EWOULDBLOCK)
            {
                std::cout << "read failed" << std::endl;
                perror ("recv");
                err_show();
                close (fd);
                return false;
            }

            break;
        }
        else if (count == 0)
        {
            // End of file. The remote has closed the
            // connection.
            std::cout << "Peer has performed an orderly shutdown" << std::endl;
            close (fd);
            return false;
        }
        else if (count == readsize)
        {
            std::cout << "Full read." << std::endl;
            return true;
        }
        else
        {
            //partial read
            std::cout << "partial read" << std::endl;
        }
    }

    return false;
}

bool Connection::write(int fd, void* buf, unsigned int writesize)
{
    ssize_t count = 0;
    int errsv = 0;

    while (1)
    {

        pthread_mutex_lock (&writeMutex_);

        count = ::send (fd, buf + count, writesize - count, MSG_DONTWAIT);
        errsv = errno;

        pthread_mutex_unlock (&writeMutex_);

        if (count == -1)
        {
            printf("%s: %s\n","send", strerror(errsv));
            // If errno == EAGAIN, that means we have written all
            //   data. So go back to the main loop.
            if (errsv != EAGAIN || errsv != EWOULDBLOCK)
            {
                err_show();
                std::cout << "write failed" << std::endl;
                perror ("send");
                close (fd);

                return false;
            }

            break;
        }
        else if (count == 0)
        {
            // End of file. The remote has closed the
            // connection.
            std::cout << "write failed: remote close" << std::endl;
            close (fd);
            break;
        }
        else if (count == writesize)
        {
            std::cout << "Full write." << std::endl;
            break;
        }
        else
        {
            //partial read
            std::cout << "partial write" << std::endl;
        }
    }

    return true;
}

bool Connection::accept(struct epoll_event* events, struct epoll_event& event1)
{
    int s;
    struct epoll_event event;

    while (1)
    {
        struct sockaddr in_addr;
        socklen_t in_len;
        int infd = -1;
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

        in_len = sizeof (in_addr);
        infd = ::accept (listenSocket_, &in_addr, &in_len);

        if (infd == -1)
        {
            if ((errno == EAGAIN) ||
                (errno == EWOULDBLOCK))
            {
                std::cout << "We have processed all incoming connections" << std::endl;
                err_show();
                break;
            }
            else
            {
                perror ("accept");
                return false;
            }
        }

        s = getnameinfo (&in_addr, in_len,
                         hbuf, sizeof(hbuf),
                         sbuf, sizeof(sbuf),
                         0);
        if (s == 0)
        {
            printf("Accepted connection on descriptor %d "
                   "(host=%s, port=%s)\n", infd, hbuf, sbuf);
        }
        else
        {
            std::cout << "client accept failed" << infd << std::endl;
            err_show();
        }

        /* Make the incoming socket non-blocking and add it to the
           list of fds to monitor. */
        s = makeSocketNonBlocking (infd);

        if (s == -1)
        {
            std::cout << "client makeSocketNonBlocking failed" << std::endl;
            err_show();
            // drop connection
        }

        event.events = EPOLLIN | EPOLLET | EPOLLOUT;
        event.data.fd = infd;

        s = epoll_ctl (ePolledFd_, EPOLL_CTL_ADD, infd, &event);

        std::cout << "client socket: " << infd << std::endl;

        if (s == -1)
        {
            std::cout << "client epoll ctl failed: " << ePolledFd_ << std::endl;
            err_show();
            // drop connection
            close (infd);
        }
    }

    return true;
}
