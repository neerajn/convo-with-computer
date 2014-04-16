/*
 * CommandData.h
 *
 */

#ifndef COMMANDDATA_H_
#define COMMANDDATA_H_

#include "messaging.h"

class CommandData
{
    public:
        CommandData ();
        ~CommandData ();

        RequestFileTestOperation& getFileTestOperationMessage ();
        void setFileTestOperationMessage (
                 RequestFileTestOperation& fileTestOperationMessage);

        RequestNextNPrimes& getNextNPrimeMessage ();
        void setNextNPrimeMessage (RequestNextNPrimes& nextNPrimeMessage);

        RequestNextPrime& getNextPrimeMessage ();
        void setNextPrimeMessage (RequestNextPrime& nextPrimeMessage);

        ResponseError& getResponseError ();
        void setResponseError (ResponseError& responseError);

        ResponseFileTestOperation& getResponseFileTestOperation ();
        void setResponseFileTestOperation (
                ResponseFileTestOperation& responseFileTestOperation);

        ResponseGetDate& getResponseGetDate ();
        void setResponseGetDate (ResponseGetDate& responseGetDate);

        ResponseHeader& getResponseHeader ();
        void setResponseHeader (ResponseHeader& responseHeader);

        ResponseNextNPrime& getResponseNextNPrimes ();
        void setResponseNextNPrimes (ResponseNextNPrime& responseNextNPrimes);

        ResponseNextPrime& getResponseNextPrime ();
        void setResponseNextPrime (ResponseNextPrime& responseNextPrime);

        ResponseTestPrime& getResponseTestPrime ();
        void setResponseTestPrime (ResponseTestPrime& responseTestPrime);

        RequestTestPrime& getTestPrimeMessage ();
        void setTestPrimeMessage (RequestTestPrime& testPrimeMessage);

        RequestGetDate& getGetDateMessage ();
        void setGetDateMessage (RequestGetDate& getDateMessage);

    private:
        CommandData ( CommandData&);
        CommandData& operator= ( CommandData&);

        RequestTestPrime m_testPrimeMessage;
        RequestNextPrime m_nextPrimeMessage;
        RequestNextNPrimes m_nextNPrimeMessage;
        RequestGetDate m_getDateMessage;
        RequestFileTestOperation m_fileTestOperationMessage;

        ResponseHeader m_responseHeader;
        ResponseTestPrime m_responseTestPrime;
        ResponseNextPrime m_responseNextPrime;
        ResponseNextNPrime m_responseNextNPrimes;
        ResponseGetDate m_responseGetDate;
        ResponseFileTestOperation m_responseFileTestOperation;
        ResponseError m_responseError;
};

#endif /* COMMANDDATA_H_ */
