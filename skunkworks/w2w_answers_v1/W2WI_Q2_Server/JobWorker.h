/*
 * JobWorker.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef JOBWORKER_H_
#define JOBWORKER_H_

#include <pthread.h>
#include <vector>

#include "Job.h"
#include "JobWorkerContext.h"
#include "ThreadPool.h"

class JobWorkerContext;

class JobWorker
{
    public:

        ~JobWorker ();

        static void* work (void* data);
        void startup (unsigned int threadNum);
        static void addWork (JobWorkerContext* jc);
        static void exit (void);

        static JobWorker& getInstance (void);


    private:

        JobWorker ();
        static JobWorker* instance_;
        static pthread_mutex_t jobWaitMutex_;
        static pthread_mutex_t jobQueueMutex_;
        static pthread_cond_t waitForWork_;
        static std::vector<JobWorkerContext*> q_;
        static ThreadPool* pool_;
};

#endif /* JOBWORKER_H_ */
