/*
 * ThreadPool.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

typedef void* (*thread_func) (void*);

class ThreadPool
{
    public:
        ThreadPool ();
        ~ThreadPool ();

        bool start (unsigned int threadNum, thread_func func);
        bool stop (void);

        unsigned int getThreadNum (void);

    private:

        unsigned int threadNum_;
};

#endif /* THREADPOOL_H_ */
