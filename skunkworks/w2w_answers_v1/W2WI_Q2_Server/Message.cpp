/*
 * Message.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */
#include <iostream>

#include "Message.h"
#include "Command.h"
#include "CommandData.h"
#include "MultCommand.h"
#include "AddCommand.h"
#include "SubtractCommand.h"
#include "PowCommand.h"
#include "XorCommand.h"


Message::Message ()
{
    // TODO Auto-generated constructor stub

}

Message::~Message ()
{
    // TODO Auto-generated destructor stub
}

Command* Message::convert(MessageCommand* mc)
{
    std::cout << "MessageCommand: " << mc->command << std::endl;
    switch(mc->command)
    {
        case MULT:
            return (new MultCommand());

        case ADD:
            return (new AddCommand());

        case SUBTRACT:
            return  (new SubtractCommand());

        case POW:
            return (new PowCommand());

        case XOR:
            return (new XorCommand());

        default:
            return NULL;
    }

    return NULL;
}

MessageResult* Message::convertResult(Command* command)
{
    return NULL;
}

