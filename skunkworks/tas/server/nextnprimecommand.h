/**
 * Command to handle next n prime numbers
 *
 */
#ifndef NEXTNPRIMECOMMAND_H_
#define NEXTNPRIMECOMMAND_H_

#include "command.h"

class NextNPrimeCommand : public Command
{
    public:
        NextNPrimeCommand ();
        ~NextNPrimeCommand ();

        bool execute(CommandData& data);
};

#endif /* NEXTNPRIMECOMMAND_H_ */

