/*
 * Message.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Command.h"

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

class Message
{
    public:

        bool parse ();

        static Command* convert(MessageCommand* mc);
        static MessageResult* convertResult(Command* command);

    private:
        Message ();
        ~Message ();
        Message (const Message&);
        Message& operator= (const Message&);

};

#endif /* MESSAGE_H_ */
