/*
 * SubtractCommand.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef SUBTRACTCOMMAND_H_
#define SUBTRACTCOMMAND_H_

#include "Command.h"

class SubtractCommand : public Command
{
    public:
        SubtractCommand ();
        ~SubtractCommand ();

        bool execute(CommandData* data);
};

#endif /* SUBTRACTCOMMAND_H_ */
