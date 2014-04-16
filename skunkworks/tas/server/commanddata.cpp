/**
 * commanddata.cpp
 *
 * Serves as a common holder, reference point for input and output
 *
 */

#include "commanddata.h"

CommandData::CommandData ()
{

}

CommandData::~CommandData ()
{
}

RequestFileTestOperation* CommandData::getFileTestOperationMessage ()
{
    return m_fileTestOperationMessage;
}

void CommandData::setFileTestOperationMessage (
        RequestFileTestOperation* fileTestOperationMessage)
{
    m_fileTestOperationMessage = fileTestOperationMessage;
}

RequestGetDate* CommandData::getGetDateMessage ()
{
    return m_getDateMessage;
}

void CommandData::setGetDateMessage (RequestGetDate* getDateMessage)
{
    m_getDateMessage = getDateMessage;
}

RequestNextNPrimes* CommandData::getNextNPrimeMessage ()
{
    return m_nextNPrimeMessage;
}

void CommandData::setNextNPrimeMessage (RequestNextNPrimes* nextNPrimeMessage)
{
    m_nextNPrimeMessage = nextNPrimeMessage;
}

RequestNextPrime* CommandData::getNextPrimeMessage ()
{
    return m_nextPrimeMessage;
}

void CommandData::setNextPrimeMessage (RequestNextPrime* nextPrimeMessage)
{
    m_nextPrimeMessage = nextPrimeMessage;
}

ResponseError* CommandData::getResponseError ()
{
    return m_responseError;
}

void CommandData::setResponseError (ResponseError* responseError)
{
    m_responseError = responseError;
}

ResponseFileTestOperation* CommandData::getResponseFileTestOperation ()
{
    return m_responseFileTestOperation;
}

void CommandData::setResponseFileTestOperation (
        ResponseFileTestOperation* responseFileTestOperation)
{
    m_responseFileTestOperation = responseFileTestOperation;
}

ResponseGetDate* CommandData::getResponseGetDate ()
{
    return m_responseGetDate;
}

void CommandData::setResponseGetDate (ResponseGetDate* responseGetDate)
{
    m_responseGetDate = responseGetDate;
}

ResponseHeader* CommandData::getResponseHeader ()
{
    return m_responseHeader;
}

void CommandData::setResponseHeader (ResponseHeader* responseHeader)
{
    m_responseHeader = responseHeader;
}

ResponseNextNPrime* CommandData::getResponseNextNPrimes ()
{
    return m_responseNextNPrimes;
}

void CommandData::setResponseNextNPrimes (
        ResponseNextNPrime* responseNextNPrimes)
{
    m_responseNextNPrimes = responseNextNPrimes;
}

ResponseNextPrime* CommandData::getResponseNextPrime ()
{
    return m_responseNextPrime;
}

void CommandData::setResponseNextPrime (ResponseNextPrime* responseNextPrime)
{
    m_responseNextPrime = responseNextPrime;
}

ResponseTestPrime* CommandData::getResponseTestPrime ()
{
    return m_responseTestPrime;
}

void CommandData::setResponseTestPrime (ResponseTestPrime* responseTestPrime)
{
    m_responseTestPrime = responseTestPrime;
}

RequestTestPrime* CommandData::getTestPrimeMessage ()
{
    return m_testPrimeMessage;
}

void CommandData::setTestPrimeMessage (RequestTestPrime* testPrimeMessage)
{
    m_testPrimeMessage = testPrimeMessage;
}
