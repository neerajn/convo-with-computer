/*
 * AddCommand.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef ADDCOMMAND_H_
#define ADDCOMMAND_H_

#include "Command.h"
#include "CommandData.h"

class AddCommand : public Command
{
    public:
        AddCommand ();
        ~AddCommand ();

        bool execute(CommandData* data);
};

#endif /* ADDCOMMAND_H_ */
