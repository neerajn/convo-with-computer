/*
 * SolutionQ2Client.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef SOLUTIONQ2CLIENT_H_
#define SOLUTIONQ2CLIENT_H_

#include "Client.h"

class SolutionQ2Client
{

public:

    ~SolutionQ2Client ();

    static  SolutionQ2Client&   getInstance    (void);
    bool                        run              (int argc, char** argv);
    bool                        validate        (int argc, char** argv);

private:

    SolutionQ2Client ();
    SolutionQ2Client (const SolutionQ2Client&);
    SolutionQ2Client& operator= (const SolutionQ2Client&);

    static void            handleSignal   (int signo);

    static SolutionQ2Client* instance_;
    Client* connection_;
    char* file_;
    char* port_;

};

#endif /* SOLUTIONQ2CLIENT_H_ */
