/**
 * messagehandler.cpp
 *
 * Handle all message parsing and analysis
 *
 */
#include <iostream>

#include "messagehandler.h"


MessageHandler::MessageHandler ()
{

}

MessageHandler::~MessageHandler ()
{
}

// process header
int MessageHandler::process (ResponseHeader& header)
{
    m_currentType = header.m_msgType;

    switch (m_currentType)
    {
        case RESPONSE_TESTPRIME:
            return sizeof(ResponseTestPrime);

        case RESPONSE_NEXTPRIME:
            return sizeof(ResponseNextPrime);

        case RESPONSE_NEXTNPRIMES:
            return sizeof(ResponseNextNPrime);

        case RESPONSE_GETDATE:
            return sizeof(ResponseGetDate);

        case RESPONSE_FILETESTOPERATION:
            return sizeof(ResponseFileTestOperation);

        case RESPONSE_ERROR:
            return sizeof(ResponseError);

        default:
            return 0;
    }

    return 0;
}

// process response body
bool MessageHandler::processResponse (char* buffer, int bodylength)
{
    switch (m_currentType)
    {
        case RESPONSE_FILETESTOPERATION:
        {
            if (((ResponseFileTestOperation*)buffer)->isFile)
            {
                std::cout << "is a file\n";
            }
            else
            {
                std::cout << "is a directory\n";
            }

            return true;
        }
        case RESPONSE_GETDATE:
        {
            std::cout << "The server date is: " << ((ResponseGetDate*)buffer)->m_date << std::endl;

            return true;
        }
        case RESPONSE_NEXTNPRIMES:
        {
            std::cout << "Response: " << std::endl;

            if (((ResponseNextNPrime*)buffer)->m_size > MAX_PRIMES_LIST_SIZE)
            {
                std::cout << "Server supports only a maximum of " << MAX_PRIMES_LIST_SIZE << " primes" << std::endl;
            }

            for (int i = 0; ((i < ((ResponseNextNPrime*)buffer)->m_size)
                && (i < MAX_PRIMES_LIST_SIZE)); ++i)
            {

                std::cout << ((ResponseNextNPrime*)buffer)->m_number[i] << std::endl;
            }

            return true;
        }
        case RESPONSE_NEXTPRIME:
        {
            std::cout << "Response: " <<  ((ResponseNextPrime*)buffer)->m_number << std::endl;

            return true;
        }
        case RESPONSE_TESTPRIME:
        {
            if (((ResponseTestPrime*)buffer)->m_isPrime)
            {
                std::cout << "is prime \n";
            }
            else
            {
                std::cout << "is not prime\n";
            }

            return true;
        }
        case RESPONSE_ERROR:
        {
            std::cout << ((ResponseError*)buffer)->m_errorMsg << "\n";
            return true;
        }
        default:
            return false;
    }

    return false;
}
