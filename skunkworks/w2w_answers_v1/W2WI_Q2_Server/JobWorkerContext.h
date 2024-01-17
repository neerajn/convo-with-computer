/*
 * JobWorkerContext.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef JOBWORKERCONTEXT_H_
#define JOBWORKERCONTEXT_H_

#include "Job.h"
#include "ClientData.h"
#include "Connection.h"

class Connection;

class JobWorkerContext
{
    public:
        JobWorkerContext ();
        ~JobWorkerContext ();

        Job* getJob (void);
        ClientData* getClientData (void);
        Connection* getConnection (void);

        void setJob (Job* job);
        void setClientData (ClientData* clientd);
        void setConnection (Connection* conn);

    private:
        JobWorkerContext (const JobWorkerContext&);
        JobWorkerContext& operator= (const JobWorkerContext&);

        Job* job_;
        ClientData* cdata_;
        Connection* connection_;

};

#endif /* JOBWORKERCONTEXT_H_ */
