/**
 * Command to handle test prime number
 *
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "testprimecommand.h"

#include "messaging.h"
#include "services.h"

TestPrimeCommand::TestPrimeCommand ()
{
}

TestPrimeCommand::~TestPrimeCommand ()
{
}

bool TestPrimeCommand::execute(CommandData& data)
{
    //validation
    // check for a limit on the value sent
    if (data.getTestPrimeMessage ()->m_number > 100000)
    {
        data.getResponseHeader()->m_msgType = RESPONSE_ERROR;
        strcpy (data.getResponseError()->m_errorMsg, "Requested number beyond specified limit.");
        return false;
    }

    std::cout << "TestPrimeCommand" << std::endl;

    data.getResponseTestPrime()->m_isPrime = Helper::isPrime (data.getTestPrimeMessage ()->m_number);
    data.getResponseHeader()->m_msgType = RESPONSE_TESTPRIME;

    return true;
}
