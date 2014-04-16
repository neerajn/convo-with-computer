/**
 * Command to handle test prime number
 *
 */
#ifndef TESTPRIMECOMMAND_H_
#define TESTPRIMECOMMAND_H_

#include "command.h"

class TestPrimeCommand : public Command
{
    public:
        TestPrimeCommand ();
        ~TestPrimeCommand ();

        bool execute(CommandData& data);
};

#endif /* TESTPRIMECOMMAND_H_ */
