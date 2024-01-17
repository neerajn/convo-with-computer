/*
 * AddCommand.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#include "AddCommand.h"

AddCommand::AddCommand ()
{
    // TODO Auto-generated constructor stub

}

AddCommand::~AddCommand ()
{
    // TODO Auto-generated destructor stub
}

bool AddCommand::execute(CommandData* data)
{
    data->setResult(data->getLHS() + data->getRHS());

    return true;
}

