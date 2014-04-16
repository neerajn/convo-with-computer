#include "nextprimecommand.h"

NextPrimeCommand::NextPrimeCommand ()
{
}

NextPrimeCommand::~NextPrimeCommand ()
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

bool getNextPrime (int64_t n)
{
    for (; !isPrime (n); ++n);

    return n;
}

bool NextPrimeCommand::execute(CommandData& data)
{
    RequestNextPrime request = data.getNextPrimeMessage ();

    data.getResponseNextPrime().m_number = getNextPrime (request.m_number);

    return true;
}

