/**
 * Command to handle next prime number
 *
 */
#ifndef NEXTPRIMECOMMAND_H_
#define NEXTPRIMECOMMAND_H_

#include "command.h"

class NextPrimeCommand : public Command
{
    public:
        NextPrimeCommand ();
        ~NextPrimeCommand ();

        bool execute(CommandData& data);
};

#endif /* NEXTPRIMECOMMAND_H_ */
