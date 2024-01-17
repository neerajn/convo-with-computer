/*
 * fibonacci_recursive.cpp
 *
 *  Created on: 08-Aug-2015
 *      Author: neerajnandakumar
 */

#include <iostream>

using namespace std;

long fib(long n)
    {
    if(n == 0)
        {
        return 0;
        }
    else if(n == 1)
        {
        return 1;
        }

    return fib(n - 1) + fib(n - 2);
    }

int main()
    {
    while(true)
        {
        cout << "Enter n" << endl;

        long n = 0;

        cin >> n;

        cout << "Fib of n = " << fib(n) << endl;
        }
    }



