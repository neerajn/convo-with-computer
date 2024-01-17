/*
 * ThreadData.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: neeraj
 */

#include <stdlib.h>

#include "ThreadData.h"

ThreadData::ThreadData ():
            threadId_ (0),
            charGroupNum_ (0),
            stringToProcess_ (NULL),
            currentPosition_ (0)
{
    // nothing to do
}

ThreadData::~ThreadData ()
{
    // no ownership of data.
}

unsigned int ThreadData::getThreadId (void) const
{
    return threadId_;
}

unsigned int ThreadData::getCharGroupNum (void) const
{
    return charGroupNum_;
}

char* ThreadData::getStringToProcess (void) const
{
    return stringToProcess_;
}

unsigned int ThreadData::getCurrentPosition (void) const
{
    return currentPosition_;
}

void ThreadData::setThreadId (unsigned int tid)
{
    threadId_ = tid;
}

void ThreadData::setCharGroupNum (unsigned int charGroupNum)
{
    charGroupNum_ = charGroupNum;
}

void ThreadData::setStringToProcess (char* stringToProcess)
{
    stringToProcess_ = stringToProcess;
}

void ThreadData::setCurrentPosition (unsigned int curPos)
{
    currentPosition_ = curPos;
}
