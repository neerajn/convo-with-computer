/**
 * Simple helper class.
 *
 */
#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <iostream>

class Helper
{

    public:
    static bool isPrime(int64_t n)
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

    static int getNextPrime (int64_t n)
    {
        for (; !isPrime (n); ++n);

        return n;
    }

    static void getNextNPrime (int64_t n, int64_t m, int64_t* resultSet, uint16_t& resultsetsize)
    {
        uint16_t i = 0;

        for ( ;i < m; ++n)
        {
            if (isPrime (n))
            {
                resultSet[i] = n;
                i++;
            }
        }
        resultsetsize = i;
    }

};

#endif
