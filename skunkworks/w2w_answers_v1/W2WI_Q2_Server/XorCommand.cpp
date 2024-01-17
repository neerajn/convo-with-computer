/*
 * XorCommand.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#include "XorCommand.h"

XorCommand::XorCommand ()
{
    // TODO Auto-generated constructor stub

}

XorCommand::~XorCommand ()
{
    // TODO Auto-generated destructor stub
}

bool XorCommand::execute(CommandData* data)
{
    data->setResult(data->getLHS() ^ data->getRHS());

    return true;
}

