/*
 * CommandData.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#include "CommandData.h"

CommandData::CommandData ():
    lhs_(0),
    rhs_(0),
    result_(0),
    executionTime_(0)
{
    // TODO Auto-generated constructor stub

}

CommandData::~CommandData ()
{
    // TODO Auto-generated destructor stub
}

long CommandData::getLHS (void)
{
    return lhs_;
}

long CommandData::getRHS (void)
{
    return rhs_;
}

long CommandData::getResult (void)
{
    return result_;
}

double CommandData::getExecutionTime (void)
{
    return executionTime_;
}

void CommandData::setLHS (long lhs)
{
    lhs_ = lhs;
}

void CommandData::setRHS (long rhs)
{
    rhs_ = rhs;
}

void CommandData::setResult (long result)
{
    result_ = result;
}

void CommandData::setExecutionTime (double et)
{
    executionTime_ = et;
}
