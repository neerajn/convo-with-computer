/**
 * messagehandler.cpp
 *
*/
#include "messagehandler.h"

#include "filetestoperationcommand.h"
#include "getdatecommand.h"
#include "testprimecommand.h"
#include "nextprimecommand.h"
#include "nextnprimecommand.h"

MessageHandler::MessageHandler ()
{

}

MessageHandler::~MessageHandler ()
{
}

int MessageHandler::process (RequestHeader& header)
{
    m_currentType = header.m_msgType;

    switch (m_currentType)
    {
        case TESTPRIME:
            return sizeof(RequestTestPrime);

        case NEXTPRIME:
            return sizeof(RequestNextPrime);

        case NEXTNPRIMES:
            return sizeof(RequestNextNPrimes);

        case GETDATE:
            return sizeof(RequestGetDate);

        case FILETESTOPERATION:
            return sizeof(RequestFileTestOperation);

        default:
            return 0;
    }

    return 0;
}

bool MessageHandler::processBody (char* buffer, int bodylength, char* returnBuffer)
{
    CommandData data;

    switch (m_currentType)
    {
        case TESTPRIME:
        {
            TestPrimeCommand testprimecommand;
            data.setTestPrimeMessage ((RequestTestPrime&)*buffer);

            return testprimecommand.execute (data);
        }
        case NEXTPRIME:
        {
            NextPrimeCommand nextprimecommand;

            data.setNextPrimeMessage ((RequestNextPrime&)*buffer);

            return nextprimecommand.execute (data);
        }
        case NEXTNPRIMES:
        {
            NextNPrimeCommand nextnprimecommand;

            data.setNextNPrimeMessage ((RequestNextNPrimes&)*buffer);

            return nextnprimecommand.execute (data);
        }
        case GETDATE:
        {
            GetDateCommand getdatecommand;

            data.setGetDateMessage ((RequestGetDate&)*buffer);

            return getdatecommand.execute (data);
        }
        case FILETESTOPERATION:
        {
            FileTestOperationCommand filetestoperationcommand;

            data.setFileTestOperationMessage ((RequestFileTestOperation&)*buffer);

            return filetestoperationcommand.execute (data);
        }
        default:
            return false;
    }

    return true;
}
