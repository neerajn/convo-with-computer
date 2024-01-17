/*
 * JobWorker.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */


#include "JobWorker.h"
#include "ThreadData.h"
#include "Job.h"
#include "Message.h"
#include "Connection.h"


pthread_mutex_t JobWorker::jobWaitMutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t JobWorker::jobQueueMutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t JobWorker::waitForWork_  = PTHREAD_COND_INITIALIZER;
std::vector<JobWorkerContext*> JobWorker::q_;
JobWorker* JobWorker::instance_ = NULL;
ThreadPool* JobWorker::pool_ = NULL;

JobWorker::JobWorker ()
{
    // TODO Auto-generated constructor stub

}

JobWorker::~JobWorker ()
{
    // TODO Auto-generated destructor stub
}

JobWorker& JobWorker::getInstance (void)
{
    if (NULL == instance_)
    {
        instance_ = new JobWorker();
    }

    return *instance_;
}

void JobWorker::startup (unsigned int threadNum)
{
    pool_ = new ThreadPool();

    pool_->start(threadNum,  (thread_func)&(JobWorker::work));
}


void* JobWorker::work (void* dta)
{
    ThreadData* data = static_cast<ThreadData*> (dta);

    while (1)
    {
        pthread_mutex_lock(&jobWaitMutex_);
        // wait for work
        std::cout << "Waiting for work: " << pthread_self() << std::endl;
        pthread_mutex_lock(&jobQueueMutex_);
        if (!q_.empty())
        {
            // dont wait.
            pthread_mutex_unlock(&jobQueueMutex_);
        }
        else
        {
            pthread_mutex_unlock(&jobQueueMutex_);
            pthread_cond_wait(&waitForWork_, &jobWaitMutex_);
        }

        pthread_mutex_unlock(&jobWaitMutex_);
        // get mutex
        JobWorkerContext* job = NULL;

        // get work
        pthread_mutex_lock(&jobQueueMutex_);
        if (!q_.empty())
        {
            job = q_.front();
            q_.erase(q_.begin());
        }
        else
        {
            pthread_mutex_unlock(&jobQueueMutex_);
            continue;
        }
        pthread_mutex_unlock(&jobQueueMutex_);

        if (job == NULL)
        {
            // unexpected error;
            continue;
        }

        // check if need to stop;
        if (job->getJob()->getJobState() == EXIT)
        {
            // yes, exit loop
            delete job;
            job = NULL;
            break;
        }
        // do work
        // do read
        else if (job->getJob()->getJobState() == READ)
        {
            Connection* conn = job->getConnection();
            int readsize = sizeof (MessageCommand);
            char* buf = new char[readsize * sizeof(char)];

            memset (buf, 0, readsize * sizeof(char));

            bool readProcessed = false;

            while (1)
            {
                if (conn->read(job->getClientData()->getFileDescriptor(),
                        buf, readsize))
                {
                    MessageCommand* mc = (MessageCommand*)buf;
                    Command* command = Message::convert(mc);

                    if (command == NULL)
                    {
                        continue;
                    }

                    if (readProcessed)
                    {
                        // additional reads.

                        Job* jobF = new Job();
                        jobF->setJobState(EXECUTE);

                        ClientData* clientdata = new ClientData();
                        clientdata->setFileDescriptor(job->getClientData()->getFileDescriptor());

                        JobWorkerContext* jobC = new JobWorkerContext();
                        jobC->setJob(jobF);
                        jobC->setConnection(job->getConnection());
                        jobC->setClientData(clientdata);

                        job = jobC;
                    }

                    CommandData* commanddata = new CommandData();
                    commanddata->setLHS(mc->lhs);
                    commanddata->setRHS(mc->rhs);

                    job->getJob()->setCommand(command);
                    job->getJob()->setCommandData(commanddata);

                    job->getJob()->setJobState(EXECUTE);
                    readProcessed = true;

                    addWork(job);
                }
                else
                {
                    break;
                }
            }
        }
        // do execute
        else if (job->getJob()->getJobState() == EXECUTE)
        {
            struct timespec start, stop;

            double accum;

            if (clock_gettime (CLOCK_REALTIME, &start) == -1)
            {
              perror ("clock gettime");
            }

            job->getJob()->getCommand()->execute (job->getJob()->getCommandData());

            if (clock_gettime (CLOCK_REALTIME, &stop) == -1)
            {
              perror ("clock gettime");
            }

            accum = (double) ( stop.tv_sec - start.tv_sec )
                  + ( (double)stop.tv_nsec - start.tv_nsec ) / 1000000000L;

            job->getJob()->getCommandData()->setExecutionTime(accum);
            job->getJob()->setJobState(WRITE);

            addWork(job);
        }
        // do write
        else if (job->getJob()->getJobState() == WRITE)
        {
            MessageResult mr;

            mr.result = job->getJob()->getCommandData()->getResult();
            mr.executiontime = job->getJob()->getCommandData()->getExecutionTime();

            Connection* conn = job->getConnection();

            conn->write(job->getClientData()->getFileDescriptor(),
                    (void*)&mr, sizeof(MessageResult));

            job->getJob()->setJobState(DONE);

            addWork(job);


        }
        // job is complete. not expected to be here.
        else if (job->getJob()->getJobState() == DONE)
        {
            // do nothing
            job = NULL;
        }
        else
        {
            // undefined state.
        }
    }

    pthread_exit(NULL);
}

void JobWorker::addWork (JobWorkerContext* jc)
{
    if (jc == NULL)
    {
        return;
    }

    // get mutex
    pthread_mutex_lock(&jobQueueMutex_);

    q_.push_back(jc);

    pthread_cond_signal(&waitForWork_);

    pthread_mutex_unlock(&jobQueueMutex_);
}

void JobWorker::exit (void)
{

    for (int i = 0; i < (pool_->getThreadNum()); ++i)
    {
        Job* exitJob = new Job();
        exitJob->setJobState(EXIT);

        JobWorkerContext* jobC = new JobWorkerContext();
        jobC->setJob(exitJob);

        pthread_mutex_lock(&jobQueueMutex_);

        q_.push_back(jobC);

        pthread_mutex_unlock(&jobQueueMutex_);
    }
}
