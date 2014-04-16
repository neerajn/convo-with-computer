/**
 * Command to handle get date
 *
 */

#include <time.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "getdatecommand.h"
#include "messaging.h"
#include "services.h"

GetDateCommand::GetDateCommand ()
{
}

GetDateCommand::~GetDateCommand ()
{
}

bool GetDateCommand::execute (CommandData& data)
{
    time_t t = time(NULL);
    struct tm tm = *localtime (&t);

    data.getResponseHeader()->m_msgType = RESPONSE_GETDATE;
    sprintf (data.getResponseGetDate()->m_date, "%d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    return true;
}

