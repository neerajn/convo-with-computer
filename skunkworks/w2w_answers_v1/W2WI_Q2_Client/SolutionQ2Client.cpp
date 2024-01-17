/*
 * SolutionQ2Client.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: neeraj
 */

#include "SolutionQ2Client.h"

SolutionQ2Client* SolutionQ2Client::instance_ = NULL;

SolutionQ2Client::SolutionQ2Client () :
        file_ (NULL),
        port_ (0)
{
    connection_ = &Client::getInstance();
}

SolutionQ2Client::~SolutionQ2Client ()
{

}

void SolutionQ2Client::handleSignal (int signo)
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
SolutionQ2Client& SolutionQ2Client::getInstance (void)
{
    if (NULL == instance_)
    {
        instance_ = new SolutionQ2Client();
    }

    return *instance_;
}

bool SolutionQ2Client::run (int argc, char** argv)
{
    // validate the input
    if (!validate (argc, argv))
    {
        return false;
    }

    // setup signal handling
    struct sigaction act;
    act.sa_handler = SolutionQ2Client::handleSignal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);

    //blocking
    connection_->start (port_, file_);

    return true;
}

bool SolutionQ2Client::validate(int argc, char** argv)
{
    if (3 != argc)
    {
        std::cout << "Error: invalid number of arguments." << std::endl;
        return false;
    }

    char* portStr = argv[1];
    file_ = argv[2];

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
