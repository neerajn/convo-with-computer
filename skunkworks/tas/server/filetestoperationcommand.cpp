/**
 * Command to handle file test operations
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "filetestoperationcommand.h"
#include "services.h"
#include "messaging.h"

FileTestOperationCommand::FileTestOperationCommand ()
{
}

FileTestOperationCommand::~FileTestOperationCommand ()
{
}

bool FileTestOperationCommand::execute (CommandData& data)
{
    struct stat s;

    if (stat (data.getFileTestOperationMessage()->m_filepathname, &s) == 0)
    {
        if (s.st_mode & S_IFDIR)
        {
            data.getResponseHeader()->m_msgType = RESPONSE_FILETESTOPERATION;
            data.getResponseFileTestOperation()->isFile = 0;
            return true;
        }
        else if (s.st_mode & S_IFREG)
        {
            data.getResponseHeader()->m_msgType = RESPONSE_FILETESTOPERATION;
            data.getResponseFileTestOperation()->isFile = 1;
            return true;
        }
        else
        {
            data.getResponseHeader()->m_msgType = RESPONSE_ERROR;
            strcpy (data.getResponseError()->m_errorMsg, "Unknown file/dir.");
            return false;
        }
    }
    data.getResponseHeader()->m_msgType = RESPONSE_ERROR;
    strcpy (data.getResponseError()->m_errorMsg, "Unknown file/dir.");
    return false;
}

