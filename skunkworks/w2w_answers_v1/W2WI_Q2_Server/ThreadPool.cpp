/*
 * ThreadPool.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */
#include <iostream>

#include "ThreadData.h"
#include "ThreadPool.h"




ThreadPool::ThreadPool ()
{
    // TODO Auto-generated constructor stub

}

ThreadPool::~ThreadPool ()
{
    // TODO Auto-generated destructor stub
}

bool ThreadPool::start (unsigned int threadNum, thread_func func)
{
    // setup and startup the threads
    threadNum_ = threadNum;
    pthread_t thr[threadNum_];
    ThreadData threadData;
    int rc;

    // create threads
    for (unsigned int i = 0; i < threadNum_; ++i)
    {
        if ((rc = pthread_create (&thr[i], NULL, func,
                &threadData)))
        {
            std::cout << "error: pthread_create, rc: " << rc << std::endl;
            return false;
        }
    }
}

bool ThreadPool::stop (void)
{
    return true;
}

unsigned int ThreadPool::getThreadNum ()
{
    return threadNum_;
}
