/*
 * SolutionQ1.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: neeraj
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>

#include "SolutionQ1.h"
#include "ThreadData.h"

SolutionQ1* SolutionQ1::instance_ = NULL;
pthread_mutex_t SolutionQ1::tlock_;

SolutionQ1::SolutionQ1 () :
        threadNum_ (0),
        charGroupNum_ (0),
        stringToProcess_ (NULL)
{
    // initialize pthread mutex
    pthread_mutex_init (&tlock_, NULL);
}

SolutionQ1::~SolutionQ1 ()
{
    // undo mutex
    pthread_mutex_destroy(&tlock_);
}

void SolutionQ1::handleSignal (int signo)
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
 * The thread work function
 */
void* SolutionQ1::threadFunc(void *arg)
{
    ThreadData* data = static_cast<ThreadData*> (arg);

    unsigned int groupSize = data->getCharGroupNum ();
    char* strToProcess = data->getStringToProcess ();
    unsigned int stringsize = strlen (strToProcess);

    char value[groupSize + sizeof (char)];

    while (1)
    {
        pthread_mutex_lock (&tlock_);

        // it the char group size is the same as the
        // length of the string, print the entire string
        // and continue. Nothing else to be done;
        if (groupSize == stringsize)
        {
            std::cout << "Thread" << pthread_self()
                    << ": " << strToProcess << std::endl;
        }
        else
        {
            // group size is less that length of the string

            // clean up out temp string holder.
            memset (value, 0, groupSize + sizeof (char));

            int currentPostion = data->getCurrentPosition();

            // We are dealing within the bounds of the length
            // of the input string.
            if ((groupSize + currentPostion) < stringsize)
            {
                memcpy (value, strToProcess + (currentPostion * sizeof(char)),
                        groupSize);
                std::cout << "Thread" << pthread_self()
                        << ": " << value << std::endl;

                data->setCurrentPosition(currentPostion + groupSize);
            }
            // We will go out of bounds, hence we need to wrap around.
            else if ((groupSize + currentPostion) >= stringsize)
            {
                // if chars left to print is equal to the group size
                // then print it and reset the current position
                if ((groupSize + currentPostion) == stringsize)
                {
                    memcpy (value, strToProcess + (currentPostion * sizeof(char)),
                            groupSize);
                    std::cout << "Thread" << pthread_self()
                            << ": " << value << std::endl;

                    data->setCurrentPosition(0);
                }
                // pure wrap around: if the number of chars to print is less
                // than group size, then print them, and print the remaining
                // from the start of the string.
                // set the current position accordingly.
                else
                {
                    memcpy (value, strToProcess + (currentPostion * sizeof(char)),
                            (stringsize - currentPostion));
                    memcpy (value + (stringsize - currentPostion), strToProcess + 0,
                            (groupSize - (stringsize - currentPostion)));
                    std::cout << "Thread" << pthread_self()
                            << ": " << value << std::endl;

                    data->setCurrentPosition(groupSize - (stringsize - currentPostion));
                }
            }
            else
            {
                std::cout << "Thread" << pthread_self() <<
                        ": never expected to be here" << std::endl;
            }
        }

        pthread_mutex_unlock(&tlock_);
    }

    pthread_exit(NULL);
}

/**
 * @Desc
 * Not meant to be thread safe. Only run by the main thread.
 * All threads are created hence forth.
 */
SolutionQ1& SolutionQ1::getInstance (void)
{
    if (NULL == instance_)
    {
        instance_ = new SolutionQ1();
    }

    return *instance_;
}

bool SolutionQ1::run (int argc, char** argv)
{
    // validate the input
    if (!validate (argc, argv))
    {
        return false;
    }

    // setup signal handling
    struct sigaction act;
    act.sa_handler = SolutionQ1::handleSignal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);

    // setup and startup the threads
    pthread_t thr[threadNum_];
    int rc;

    /* create a ThreadData argument array */
    ThreadData threadData;
    threadData.setCharGroupNum (charGroupNum_);
    threadData.setStringToProcess (stringToProcess_);
    threadData.setCurrentPosition (0);

    /* create threads */
    for (unsigned int i = 0; i < threadNum_; ++i)
    {
        if ((rc = pthread_create (&thr[i], NULL, SolutionQ1::threadFunc, &threadData)))
        {
            std::cout << "error: pthread_create, rc: " << rc << std::endl;
            return false;
        }
    }
    /* block until all threads complete */
    for (unsigned int i = 0; i < threadNum_; ++i)
    {
        pthread_join(thr[i], NULL);
    }

    return true;
}

bool SolutionQ1::validate(int argc, char** argv)
{
    if (4 != argc)
    {
        std::cout << "Error: invalid number of arguments." << std::endl;
        return false;
    }

    char* strdata = argv[1];
    char* charGroupNumStr = argv[2];
    char* threadNumStr = argv[3];
    unsigned int strlength = strlen(strdata);

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

    int charGroupNumStrSize = strlen(charGroupNumStr);
    for (int i = 0; i < charGroupNumStrSize; ++i)
    {
        if (!isdigit(charGroupNumStr[i]))
        {
            std::cout << "Error: Invalid char group count. It must be a number."
                      << std::endl;

            return false;
        }
    }

    charGroupNum_ = atoi (charGroupNumStr);

    if (!charGroupNum_)
    {
        std::cout << "Error: Char group count cant be zero."
                  << std::endl;

        return false;
    }

    stringToProcess_ = strdata;

    if (strlength < charGroupNum_)
    {
        std::cout << "Error: Group size greater than string size. Invalid input."
                  << std::endl;

        return false;
    }

    std::cout << "Using " << threadNum_<< " threads to print " <<
            stringToProcess_ << " alternatively in set of " << charGroupNum_
            << " chars." << std::endl << std::endl;

    return true;
}
