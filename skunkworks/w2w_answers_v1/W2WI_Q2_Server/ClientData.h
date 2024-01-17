/*
 * ClientData.h
 *
 *  Created on: Apr 15, 2013
 *      Author: neeraj
 */

#ifndef CLIENTDATA_H_
#define CLIENTDATA_H_

#include <pthread.h>

class ClientData
{
    public:
        ClientData ();
        virtual ~ClientData ();

        int getFileDescriptor (void);
        void setFileDescriptor (int fd);

    private:
        ClientData (const ClientData&);
        ClientData& operator= (const ClientData&);

        int fileDescriptor_;
};

#endif /* CLIENTDATA_H_ */
