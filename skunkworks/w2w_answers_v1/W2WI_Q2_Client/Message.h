/*
 * Message.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

typedef struct MessageCommand_
{
        unsigned int command;
        long lhs;
        long rhs;
} MessageCommand;

typedef struct MessageResult_
{
        long result;
        double executiontime;
} MessageResult;

#endif /* MESSAGE_H_ */
