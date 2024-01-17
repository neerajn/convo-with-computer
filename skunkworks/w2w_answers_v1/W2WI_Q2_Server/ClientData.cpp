/*
 * ClientData.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: neeraj
 */

#include "ClientData.h"

ClientData::ClientData ():
    fileDescriptor_ (0)
{
    // TODO Auto-generated constructor stub

}

ClientData::~ClientData ()
{
    // TODO Auto-generated destructor stub
}

int ClientData::getFileDescriptor (void)
{
    return fileDescriptor_;
}

void ClientData::setFileDescriptor (int fd)
{
    fileDescriptor_ = fd;
}

