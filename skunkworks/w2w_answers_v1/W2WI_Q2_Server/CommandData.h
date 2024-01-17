/*
 * CommandData.h
 *
 *  Created on: Apr 14, 2013
 *      Author: neeraj
 */

#ifndef COMMANDDATA_H_
#define COMMANDDATA_H_

class CommandData
{
    public:
        CommandData ();
        ~CommandData ();

        long getLHS (void);
        long getRHS (void);
        long getResult (void);
        double  getExecutionTime (void);

        void setLHS (long);
        void setRHS (long);
        void setResult (long);
        void setExecutionTime (double);

    private:
        CommandData (const CommandData&);
        CommandData& operator= (const CommandData&);

        long lhs_;
        long rhs_;
        long result_;
        double executionTime_;
};

#endif /* COMMANDDATA_H_ */
