/*
 * SubtractCommand.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#include "SubtractCommand.h"

SubtractCommand::SubtractCommand ()
{
    // TODO Auto-generated constructor stub

}

SubtractCommand::~SubtractCommand ()
{
    // TODO Auto-generated destructor stub
}

bool SubtractCommand::execute(CommandData* data)
{
    data->setResult(data->getLHS() - data->getRHS());

    return true;
}

