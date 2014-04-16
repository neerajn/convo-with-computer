/**
 * All messages are parsed and handled here.
 *
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>

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

void MessageHandler::process (char* buffer, int bodylength, char* returnBuffer, uint16_t& returnBufferSize)
{
    CommandData data;
    switch (m_currentType)
    {
        case TESTPRIME:
        {
            std::cout << "TestPrimeCommand\n";
            TestPrimeCommand testprimecommand;
            data.setTestPrimeMessage ((RequestTestPrime*)buffer);
            data.setResponseHeader ((ResponseHeader*) returnBuffer);
            data.setResponseError ((ResponseError*) (returnBuffer + sizeof (ResponseHeader)));
            data.setResponseTestPrime ((ResponseTestPrime*) (returnBuffer + sizeof (ResponseHeader)));

            std::cout << data.getTestPrimeMessage()->m_number << std::endl;

            if (testprimecommand.execute (data))
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseTestPrime);
            }
            else
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseError);
            }
            break;
        }
        case NEXTPRIME:
        {
            std::cout << "NextPrimeCommand\n";
            NextPrimeCommand nextprimecommand;

            data.setNextPrimeMessage ((RequestNextPrime*)buffer);
            data.setResponseHeader ((ResponseHeader*) returnBuffer);
            data.setResponseError ((ResponseError*) (returnBuffer + sizeof (ResponseHeader)));
            data.setResponseNextPrime ((ResponseNextPrime*) (returnBuffer + sizeof (ResponseHeader)));

            if (nextprimecommand.execute (data))
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseNextPrime);
            }
            else
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseError);
            }
            break;
        }
        case NEXTNPRIMES:
        {
            std::cout << "NextNPrimeCommand\n";
            NextNPrimeCommand nextnprimecommand;

            data.setNextNPrimeMessage ((RequestNextNPrimes*)buffer);
            data.setResponseHeader ((ResponseHeader*) returnBuffer);
            data.setResponseError ((ResponseError*) (returnBuffer + sizeof (ResponseHeader)));
            data.setResponseNextNPrimes ((ResponseNextNPrime*) (returnBuffer + sizeof (ResponseHeader)));

            if (nextnprimecommand.execute (data))
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseNextNPrime);
            }
            else
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseError);
            }
            break;
        }
        case GETDATE:
        {
            std::cout << "GetDateCommand\n";
            GetDateCommand getdatecommand;

            data.setGetDateMessage ((RequestGetDate*)buffer);
            data.setResponseHeader ((ResponseHeader*) returnBuffer);
            data.setResponseError ((ResponseError*) (returnBuffer + sizeof (ResponseHeader)));
            data.setResponseGetDate ((ResponseGetDate*) (returnBuffer + sizeof (ResponseHeader)));

            if (getdatecommand.execute (data))
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseGetDate);
            }
            else
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseError);
            }
            break;
        }
        case FILETESTOPERATION:
        {
            std::cout << "FileTestOperationCommand\n";
            FileTestOperationCommand filetestoperationcommand;

            data.setFileTestOperationMessage ((RequestFileTestOperation*)buffer);
            data.setResponseHeader ((ResponseHeader*) returnBuffer);
            data.setResponseError ((ResponseError*) (returnBuffer + sizeof (ResponseHeader)));
            data.setResponseFileTestOperation ((ResponseFileTestOperation*) (returnBuffer + sizeof (ResponseHeader)));

            if (filetestoperationcommand.execute (data))
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseFileTestOperation);
            }
            else
            {
                returnBufferSize = sizeof (ResponseHeader) + sizeof (ResponseError);
            }
            break;
        }
        default:
            break;
    }
}
