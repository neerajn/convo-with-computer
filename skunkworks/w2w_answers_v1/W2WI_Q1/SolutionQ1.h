/*
 * SolutionQ1.h
 *
 *  Created on: Apr 13, 2013
 *      Author: neeraj
 */

#ifndef SOLUTIONQ1_H_
#define SOLUTIONQ1_H_

#include <pthread.h>

class SolutionQ1
{
    public:

        ~SolutionQ1 ();

        static  SolutionQ1&     getInstance    (void);
        bool                    run              (int argc, char** argv);
        bool                    validate        (int argc, char** argv);

    private:

        SolutionQ1 ();
        SolutionQ1 (const SolutionQ1&);
        SolutionQ1& operator= (const SolutionQ1&);

        static void*           threadFunc     (void*);
        static void            handleSignal   (int signo);

        static SolutionQ1* instance_;
        static pthread_mutex_t tlock_;
        unsigned int threadNum_;
        unsigned int charGroupNum_;
        char* stringToProcess_;

};

#endif /* SOLUTIONQ1_H_ */
