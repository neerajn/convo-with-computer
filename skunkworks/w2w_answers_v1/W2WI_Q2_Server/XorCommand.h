/*
 * XorCommand.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef XORCOMMAND_H_
#define XORCOMMAND_H_

#include "Command.h"

class XorCommand : public Command
{
    public:
        XorCommand ();
        ~XorCommand ();

        bool execute(CommandData* data);
};

#endif /* XORCOMMAND_H_ */
