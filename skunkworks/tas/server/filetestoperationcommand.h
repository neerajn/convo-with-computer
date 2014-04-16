/**
 * Command to handle file test operations
 *
 */
#ifndef FILETESTOPERATIONCOMMAND_H_
#define FILETESTOPERATIONCOMMAND_H_

#include "command.h"

class FileTestOperationCommand : public Command
{
    public:
        FileTestOperationCommand ();
        ~FileTestOperationCommand ();

        bool execute(CommandData& data);
};

#endif /* FILETESTOPERATIONCOMMAND_H_ */

