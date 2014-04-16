/**
 * Command to handle next  prime number
 *
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "nextprimecommand.h"
#include "messaging.h"
#include "services.h"


NextPrimeCommand::NextPrimeCommand ()
{
}

NextPrimeCommand::~NextPrimeCommand ()
{
}

bool NextPrimeCommand::execute(CommandData& data)
{
    //validation
    // check for a limit on the value sent
    if (data.getNextPrimeMessage ()->m_number > 100000)
    {
        data.getResponseHeader()->m_msgType = RESPONSE_ERROR;
        strcpy (data.getResponseError()->m_errorMsg, "Requested number beyond specified limit.");
        return false;
    }

    data.getResponseNextPrime()->m_number = Helper::getNextPrime (data.getNextPrimeMessage ()->m_number);
    data.getResponseHeader()->m_msgType = RESPONSE_NEXTPRIME;

    return true;
}

