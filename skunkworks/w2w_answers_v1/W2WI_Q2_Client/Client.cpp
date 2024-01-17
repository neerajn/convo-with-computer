/*
 * Client.cpp
 *
 *  Created on: Apr 14, 2013Socket::Client ()
 *      Author: neeraj
 */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>

#include "Command.h"
#include "Client.h"
#include "Message.h"

#define MAXEVENTS 64

using namespace std;

Client* Client::instance_ = NULL;
std::vector<MessageCommand*> Client::jobs_;

char* Client::port_ = 0;
int Client::socket_ = 0;
int Client::ePolledFd_ = 0;

Client::Client ()
{
    // TODO Auto-generated constructor stub

}

Client::~Client ()
{
    // TODO Auto-generated destructor stub
}

Client& Client::getInstance (void)
{
    if (NULL == instance_)
    {
        instance_ = new Client();
    }

    return *instance_;
}

int Client::makeSocketNonBlocking (int sfd)
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

int Client::createClient (char* port)
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
        fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
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

        s = connect(sfd, rp->ai_addr, rp->ai_addrlen);

        if (s == 0)
        {
            // We managed to connect successfully
            std::cout << "connected" << std::endl;
            break;
        }
        else
        {
            std::cout << "connect failed" << std::endl;
        }

        close(sfd);
    }

    if (rp == NULL)
    {
        err_show();
        fprintf (stderr, "Could not connect\n");
        return -1;
    }

    freeaddrinfo (result);

    return sfd;
}

bool Client::start(char* port, char* file)
{
    int s;
    struct epoll_event  event;
    struct epoll_event* events;

    ifstream infile;
    string sLine = "";
    infile.open(file);

    while (!infile.eof())
    {
        getline(infile, sLine);

        if(sLine.length() == 0)
        {
            continue;
        }

        // MULT 1000 2500
        istringstream iss(sLine);
        vector<string> tokens;
        tokens.clear();

        copy(istream_iterator<string>(iss),
                 istream_iterator<string>(),
                 back_inserter<vector<string> >(tokens));

        if (tokens.size() != 3)
        {
            continue;
        }

        MessageCommand* mc = new MessageCommand;

        mc->lhs = atoi(tokens[1].c_str());
        mc->rhs = atoi(tokens[2].c_str());

        if (tokens[0].compare("MULT") == 0)
        {
            mc->command = MULT;
        }
        else if (tokens[0].compare("ADD") == 0)
        {
            mc->command = ADD;
        }
        else if (tokens[0].compare("SUB") == 0)
        {
            mc->command = SUBTRACT;
        }
        else if (tokens[0].compare("POW") == 0)
        {
            mc->command = POW;
        }
        else if (tokens[0].compare("XOR") == 0)
        {
            mc->command = XOR;
        }
        else
        {
            continue;
        }

        std::cout << "Command: " << tokens[0] << std::endl;
        std::cout << "lhs: " << mc->lhs << std::endl;
        std::cout << "rhs: " << mc->rhs << std::endl;

        jobs_.push_back(mc);

    }
    infile.close();

    socket_ = createClient (port);

    if (socket_ == -1)
    {
        err_show();
        std::cout << "create failed" << std::endl;
        return false;
    }

    s = makeSocketNonBlocking (socket_);

    if (s == -1)
    {
        err_show();
        std::cout << "makeSocketNonBlocking failed" << std::endl;
        return false;
    }

    ePolledFd_ = epoll_create1 (0);

    if (ePolledFd_ == -1)
    {
        err_show();
        std::cout << "epoll create failed" << std::endl;
        return false;
    }

    event.data.fd = socket_;
    event.events = EPOLLIN | EPOLLOUT | EPOLLET;
    s = epoll_ctl (ePolledFd_, EPOLL_CTL_ADD, socket_, &event);

    if (s == -1)
    {
        err_show();
        return false;
    }

    // Buffer where events are returned
    events = (epoll_event*)calloc (MAXEVENTS, sizeof(event));

    // The event loop
    while (1)
    {
        int n, i;
        do
        {
            n = epoll_wait (ePolledFd_, events, MAXEVENTS, -1);
        } while (n < 0 && errno == EINTR);


        for (i = 0; i < n; i++)
        {
            if(events[i].events  & EPOLLIN)
            {
                // We have data on the fd waiting to be read. Read and
                // display it. We must read whatever data is available
                // completely, as we are running in edge-triggered mode
                // and won't get a notification again for the same
                // data.
                read(events[i].data.fd);
            }
            else if(events[i].events  & EPOLLOUT)
            {
                for (int i = 0; i < jobs_.size(); ++i )
                    write (socket_, (void*)(jobs_[i]), sizeof(MessageCommand));
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
                fprintf (stderr, "epoll error\n");
                std::cout << "Closing connection" << std::endl;
                close (events[i].data.fd);
                exit(1);
                continue;
            }
        }
    }

    free (events);
    close (socket_);
}

void Client::err_show()
{
    if(EBADF == errno)
    {
        std::cout << "error at epoll_ctl, error  is EBADF" << std::endl;
    }
    else if(EEXIST == errno)
    {
        std::cout << "error at epoll_ctl, error  is EEXIST" << std::endl;
    }
    else if(EINVAL == errno)
    {
        std::cout << "error at epoll_ctl, error  is EINVAL" << std::endl;
    }
    else if(ENOENT == errno)
    {
        std::cout << "error at epoll_ctl, error  is ENOENT" << std::endl;
    }
    else if(ENOMEM == errno)
    {
        std::cout << "error at epoll_ctl, error  is ENOMEM" << std::endl;
    }
    else if(ENOSPC == errno)
    {
        std::cout << "error at epoll_ctl, error  is ENOSPC" << std::endl;
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

bool Client::read(int fd)
{
    ssize_t count = 0;
    ssize_t readsize = sizeof(MessageResult);
    char buf[readsize];

    memset (buf, 0, readsize);

    while (1)
    {
        count = ::read (fd, buf + count, readsize - count);

        if (count == -1)
        {
            // If errno == EAGAIN, that means we have read all
            //   data. So go back to the main loop.
            if (errno != EAGAIN)
            {
                std::cout << "read failed" << std::endl;
                perror ("read");
                close (fd);
                return false;
            }
            break;
        }
        else if (count == 0)
        {
            // End of file. The remote has closed the
            // connection.
            std::cout << "read failed: remote close" << std::endl;
            close (fd);
            break;
        }
        else if (count == readsize)
        {
            std::cout << "Full message read." << std::endl;
            MessageResult* mc = (MessageResult*)buf;

            std::cout << "Result: " << mc->result << std::endl;
            std::cout << "Execution Time: " << mc->executiontime << std::endl;

            jobs_.erase (jobs_.begin());


            if (!jobs_.size())
            {
                exit(0);
            }

            break;
        }
        else
        {
            //partial read
            std::cout << "partial read" << std::endl;
        }
    }

    return true;
}


bool Client::write(int fd, void* buf, unsigned int size)
{
    ssize_t count;

    count = ::write (fd, buf, size);

    if (count == -1)
    {
        // If errno == EAGAIN, that means we have written all
        //   data. So go back to the main loop.
        if (errno != EAGAIN)
        {
            std::cout << "write failed" << std::endl;
            close (fd);
            perror ("write");
            return false;
        }
    }
    else if (count == 0)
    {
        // End of file. The remote has closed the
        // connection.
        std::cout << "write failed: remote close" << std::endl;
        close (fd);
    }
    else if (count == size)
    {
        std::cout << "write success." << std::endl;
    }

    return true;
}
