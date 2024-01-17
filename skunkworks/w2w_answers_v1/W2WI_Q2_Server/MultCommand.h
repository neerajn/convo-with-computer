/*
 * MultCommand.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef MULTCOMMAND_H_
#define MULTCOMMAND_H_

#include "Command.h"

class MultCommand : public Command
{
    public:
        MultCommand ();
        ~MultCommand ();

        bool execute(CommandData* data);
};

#endif /* MULTCOMMAND_H_ */
