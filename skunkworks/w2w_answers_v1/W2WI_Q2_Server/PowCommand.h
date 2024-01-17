/*
 * PowCommand.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef POWCOMMAND_H_
#define POWCOMMAND_H_

#include "Command.h"

class PowCommand : public Command
{
    public:
        PowCommand ();
        ~PowCommand ();

        bool execute(CommandData* data);
};

#endif /* POWCOMMAND_H_ */
