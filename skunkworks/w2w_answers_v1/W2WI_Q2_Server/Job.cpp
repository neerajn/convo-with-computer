/*
 * Job.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#include <stdlib.h>

#include "Job.h"

Job::Job () :
    command_ (NULL),
    commandData_ (NULL),
    state_ (READ),
    rawMessage_ (NULL),
    messageSize_ (0)
{

}

Job::~Job ()
{
}

JobState Job::getJobState ()
{
    return state_;
}

Command* Job::getCommand ()
{
    return command_;
}

CommandData* Job::getCommandData ()
{
    return commandData_;
}

void* Job::getRawMessage ()
{
    return rawMessage_;
}

unsigned int  Job::getMessageSize ()
{
    return messageSize_;
}

void Job::setJobState (JobState js)
{
    state_ = js;
}

void Job::setCommand  (Command* command)
{
    command_ = command;
}

void Job::setCommandData  (CommandData* commanddata)
{
    commandData_ = commanddata;
}

void Job::setRawMessage  (void* msg)
{
    rawMessage_ = msg;
}

void Job::setMessageSize  (unsigned int size)
{
    messageSize_ = size;
}


