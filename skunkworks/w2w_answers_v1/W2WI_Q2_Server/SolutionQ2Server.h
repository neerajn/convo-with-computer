/*
 * SolutionQ2Server.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef SOLUTIONQ2SERVER_H_
#define SOLUTIONQ2SERVER_H_

#include "JobWorker.h"
#include "Connection.h"

class SolutionQ2Server
{

public:

    ~SolutionQ2Server ();

    static  SolutionQ2Server&   getInstance    (void);
    bool                        run              (int argc, char** argv);
    bool                        validate        (int argc, char** argv);

private:

    SolutionQ2Server ();
    SolutionQ2Server (const SolutionQ2Server&);
    SolutionQ2Server& operator= (const SolutionQ2Server&);

    static void            handleSignal   (int signo);

    static SolutionQ2Server* instance_;
    JobWorker* workers_;
    Connection* connection_;
    unsigned int threadNum_;
    char* port_;

};

#endif /* SOLUTIONQ2SERVER_H_ */
