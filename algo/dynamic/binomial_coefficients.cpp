/*
 * binomial_coefficients.cpp
 *
 *  Created on: 08-Aug-2015
 *      Author: neerajnandakumar
 */

#include <iostream>

using namespace std;

const unsigned long MAXSIZE = 100;

unsigned long compute(unsigned int n, unsigned int k)
    {
    unsigned long PascalTriangle[MAXSIZE][MAXSIZE];

    for(int i = 0; i <= n; ++i)
        {
        PascalTriangle[i][0] = 1;
        }

    for(int j = 1; j <= n; ++j)
        {
        PascalTriangle[j][j] = 1;
        }

    for(int i = 1; i <= n; ++i)
        {
        for(int j = 1; j <= i; ++j)
            {
            PascalTriangle[i][j] = PascalTriangle[i - 1][j - 1] + PascalTriangle[i - 1][j];
            }
        }

    return PascalTriangle[n][k];
    }

int main()
    {
    unsigned int n = 0;
    unsigned int k = 0;

    cout << "Enter n "; cin >> n;
    cout << "Enter k "; cin >> k;

    cout << "binomial coefficient at n,k = "  << compute(n, k) << endl;

    }
