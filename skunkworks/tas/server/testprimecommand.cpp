#include "testprimecommand.h"

TestPrimeCommand::TestPrimeCommand ()
{
}

TestPrimeCommand::~TestPrimeCommand ()
{
}

bool isPrime(int64_t n)
{
    if (n < 2)
    {
        return false;
    }

    for (int64_t i = 2; true; ++i)
    {
        int64_t qo = n / i;

        if (qo < i)
        {
            return true;
        }

        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

bool TestPrimeCommand::execute(CommandData& data)
{
    RequestTestPrime request = data.getTestPrimeMessage ();

    data.getResponseTestPrime().m_isPrime = isPrime (request.m_number);

    return true;
}
