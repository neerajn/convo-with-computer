/*
 * Command.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "CommandData.h"

enum CommandEnum
{
    MULT = 0,
    ADD,
    SUBTRACT,
    POW,
    XOR
};

class Command
{
    public:
        Command ()
        {

        }

        virtual ~Command ()
        {

        }

        virtual bool execute (CommandData* data) = 0;

    private:
        Command (const Command&);
        Command& operator= (const Command&);
};

#endif /* COMMAND_H_ */
