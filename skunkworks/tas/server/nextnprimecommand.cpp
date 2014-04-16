/**
 * Command to handle next n prime numbers
 *
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "nextnprimecommand.h"
#include "messaging.h"
#include "services.h"

NextNPrimeCommand::NextNPrimeCommand ()
{
}

NextNPrimeCommand::~NextNPrimeCommand ()
{
}

bool NextNPrimeCommand::execute(CommandData& data)
{
    //validation
    // check for a limit on the value sent
    if (data.getNextNPrimeMessage ()->m_number > 100000)
    {
        data.getResponseHeader()->m_msgType = RESPONSE_ERROR;
        strcpy (data.getResponseError()->m_errorMsg, "Requested number beyond specified limit.");
        return false;
    }

    if (data.getNextNPrimeMessage ()->m_howMany > 100000 || data.getNextNPrimeMessage ()->m_howMany < data.getNextNPrimeMessage ()->m_number)
    {
        data.getResponseHeader()->m_msgType = RESPONSE_ERROR;
        strcpy (data.getResponseError()->m_errorMsg, "Invalid input.");
        return false;
    }

    Helper::getNextNPrime (data.getNextNPrimeMessage ()->m_number, data.getNextNPrimeMessage ()->m_howMany,
                    data.getResponseNextNPrimes()->m_number, data.getResponseNextNPrimes()->m_size);
    data.getResponseHeader()->m_msgType = RESPONSE_NEXTNPRIMES;

    return true;
}

