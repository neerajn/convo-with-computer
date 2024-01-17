/*
 * Job.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef JOB_H_
#define JOB_H_

#include "Command.h"
#include "CommandData.h"
#include "Message.h"

enum JobState
{
    EXIT = -1,
    READ = 0,
    EXECUTE,
    WRITE,
    DONE
};

class Job
{
    public:
        Job ();
        ~Job ();

        JobState        getJobState ();
        Command*        getCommand  ();
        CommandData*    getCommandData  ();
        void*          getRawMessage  ();
        unsigned int  getMessageSize  ();

        void            setJobState (JobState js);
        void            setCommand  (Command* command);
        void            setCommandData  (CommandData* command);
        void            setRawMessage  (void* msg);
        void            setMessageSize  (unsigned int size);

    private:

        Job (const Job&);
        Job& operator= (const Job&);

        Command* command_;
        CommandData* commandData_;
        JobState state_;
        void* rawMessage_;
        unsigned int messageSize_;

};

#endif /* JOB_H_ */
