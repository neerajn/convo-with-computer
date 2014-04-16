#ifndef GETDATECOMMAND_H_
#define GETDATECOMMAND_H_

#include "command.h"

class GetDateCommand : public Command
{
    public:
        GetDateCommand ();
        ~GetDateCommand ();

        bool execute(CommandData& data);
};

#endif /* GETDATECOMMAND_H_ */

