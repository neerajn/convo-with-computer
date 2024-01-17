/*
 * PowCommand.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#include <math.h>

#include "PowCommand.h"

PowCommand::PowCommand ()
{
    // TODO Auto-generated constructor stub

}

PowCommand::~PowCommand ()
{
    // TODO Auto-generated destructor stub
}

bool PowCommand::execute(CommandData* data)
{
    data->setResult(pow (data->getLHS(), data->getRHS()));

    return true;
}

