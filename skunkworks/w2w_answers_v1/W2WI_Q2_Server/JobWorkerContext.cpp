/*
 * JobWorkerContext.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#include <stdlib.h>

#include "JobWorkerContext.h"

JobWorkerContext::JobWorkerContext () :
    job_(NULL),
    cdata_ (0),
    connection_ (NULL)
{
    // TODO Auto-generated constructor stub

}

JobWorkerContext::~JobWorkerContext ()
{
    if (job_ != NULL)
    {
        delete job_;

        job_ = NULL;
    }

    // we dont own client data
}

Job* JobWorkerContext::getJob (void)
{
    return job_;
}

ClientData* JobWorkerContext::getClientData (void)
{
    return cdata_;
}

Connection* JobWorkerContext::getConnection (void)
{
    return connection_;
}

void JobWorkerContext::setJob (Job* job)
{
    job_ = job;
}

void JobWorkerContext::setClientData (ClientData* clientdata)
{
    cdata_ = clientdata;
}

void JobWorkerContext::setConnection (Connection* conn)
{
    connection_ = conn;
}
