/*
 * fibonacci_dp.cpp
 *
 *  Created on: 08-Aug-2015
 *      Author: neerajnandakumar
 */

#include <iostream>

using namespace std;

// const space and linear time.
unsigned long long fib(unsigned long n)
    {
    unsigned long long prev2 = 0;
    unsigned long long prev1 = 1;
    unsigned long long next = 0;

    if(n == 0)
        return prev2;
    else if(n == 1)
        return prev1;

    for(unsigned long i = 2; i <= n; ++i)
        {
        next = prev1 + prev2;
        prev2 = prev1;
        prev1 = next;
        }

    return next;
    }

int main()
    {
    unsigned long n = 0;

    while(n != -1)
        {
        cout << "Enter n or -1 to quit." << endl;

        n = 0;

        cin >> n;

        cout << "Fib of n = " << fib(n) << endl;
        }
    }



