/*
 * MultCommand.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#include "MultCommand.h"

MultCommand::MultCommand ()
{
    // TODO Auto-generated constructor stub

}

MultCommand::~MultCommand ()
{
    // TODO Auto-generated destructor stub
}

bool MultCommand::execute(CommandData* data)
{
    data->setResult(data->getLHS() * data->getRHS());

    return true;
}

