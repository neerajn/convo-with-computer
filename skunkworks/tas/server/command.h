/** 
 * Command.h
 * 
 * Interface to a command class
 *
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "commanddata.h"

class Command
{
    public:
        Command ()
        {

        }

        virtual ~Command ()
        {

        }

        virtual bool execute (CommandData& data) = 0;

    private:
        Command (const Command&);
        Command& operator= (const Command&);
};

#endif /* COMMAND_H_ */

