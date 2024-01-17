/*
 * SolutionQ2Server.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: neeraj
 */

#include "SolutionQ2Server.h"
#include "ThreadData.h"

SolutionQ2Server* SolutionQ2Server::instance_ = NULL;

SolutionQ2Server::SolutionQ2Server () :
        threadNum_ (0),
        port_ (0)
{
    workers_ = &JobWorker::getInstance();
    connection_ = &Connection::getInstance();
}

SolutionQ2Server::~SolutionQ2Server ()
{

}

void SolutionQ2Server::handleSignal (int signo)
{
    std::cout << "Got a term signal. terminating..." << std::endl;

    switch (signo)
    {
        case SIGINT:
            exit(0);
            break;
        default:
            break;
    }
}

/**
 * @Desc
 * Not meant to be thread safe. Only run by the main thread.
 * All threads are created hence forth.
 */
SolutionQ2Server& SolutionQ2Server::getInstance (void)
{
    if (NULL == instance_)
    {
        instance_ = new SolutionQ2Server();
    }

    return *instance_;
}

bool SolutionQ2Server::run (int argc, char** argv)
{
    // validate the input
    if (!validate (argc, argv))
    {
        return false;
    }

    // setup signal handling
    struct sigaction act;
    act.sa_handler = SolutionQ2Server::handleSignal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);


    workers_->startup(threadNum_);
    //blocking
    connection_->start(port_);

    return true;
}

bool SolutionQ2Server::validate(int argc, char** argv)
{
    if (3 != argc)
    {
        std::cout << "Error: invalid number of arguments." << std::endl;
        return false;
    }

    char* portStr = argv[1];
    char* threadNumStr = argv[2];

    int threadNumStrSize = strlen(threadNumStr);
    for (int i = 0; i < threadNumStrSize; ++i)
    {
        if (!isdigit(threadNumStr[i]))
        {
            std::cout << "Error: Invalid thread count. It must be a number."
                      << std::endl;

            return false;
        }
    }

    threadNum_ = atoi (threadNumStr);

    if (!threadNum_)
    {
        std::cout << "Error: Thread count cant be zero."
                  << std::endl;

        return false;
    }

    int portStrSize = strlen(portStr);
    for (int i = 0; i < portStrSize; ++i)
    {
        if (!isdigit(portStr[i]))
        {
            std::cout << "Error: Invalid char group count. It must be a number."
                      << std::endl;

            return false;
        }
    }

    port_ = portStr;

    return true;
}
