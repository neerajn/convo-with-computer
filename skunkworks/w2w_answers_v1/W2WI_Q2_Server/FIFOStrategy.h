/*
 * FIFOStrategy.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef FIFOSTRATEGY_H_
#define FIFOSTRATEGY_H_

#include "JobWorkerStrategy.h"

class FIFOStrategy: public JobWorkerStrategy
{
    public:
        FIFOStrategy ();
        ~FIFOStrategy ();
};

#endif /* FIFOSTRATEGY_H_ */
