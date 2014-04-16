#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "filetestoperationcommand.h"

FileTestOperationCommand::FileTestOperationCommand ()
{
}

FileTestOperationCommand::~FileTestOperationCommand ()
{
}

bool FileTestOperationCommand::execute (CommandData& data)
{
    struct stat s;
    if (stat (data.getFileTestOperationMessage().m_filepathname, &s) == 0)
    {
        if (s.st_mode & S_IFDIR)
        {
        }
        else if (s.st_mode & S_IFREG)
        {
        }
        else
        {
        }
    }
    else
    {
        //error
    }

    return true;
}

