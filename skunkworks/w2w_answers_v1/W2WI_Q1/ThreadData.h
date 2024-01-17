/*
 * ThreadData.h
 *
 *  Created on: Apr 13, 2013
 *      Author: neeraj
 */

#ifndef THREADDATA_H_
#define THREADDATA_H_


/* create thread argument class for thread work function */
class ThreadData
{
    public:

        ThreadData ();
        ~ThreadData ();

        unsigned int   getThreadId (void) const;
        unsigned int   getCharGroupNum (void) const;
        char*           getStringToProcess (void) const;
        unsigned int   getCurrentPosition (void) const;

        void            setThreadId (unsigned int);
        void            setCharGroupNum (unsigned int);
        void            setStringToProcess (char*);
        void            setCurrentPosition (unsigned int);

    private:

        ThreadData (const ThreadData&);
        ThreadData& operator=(const ThreadData&);

        unsigned int threadId_;
        unsigned int charGroupNum_;
        char*         stringToProcess_;
        int           currentPosition_;

};

#endif /* THREADDATA_H_ */
