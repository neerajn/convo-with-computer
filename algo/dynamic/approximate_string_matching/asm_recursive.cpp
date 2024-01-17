/*
 * asm_recursive.cpp
 *
 *  Created on: 09-Aug-2015
 *      Author: neerajnandakumar
 */

#include <iostream>
#include <string>

using namespace std;

const unsigned int MATCH  = 0;
const unsigned int INSERT = 1;
const unsigned int DELETE = 2;

const unsigned int OPERATIONCOUNT = 3;

unsigned int match(char x, char y)
    {
    if(x == y)
        {
        return 0;
        }
    return 1;
    }

unsigned int indel(char x)
    {
    return 1;
    }

unsigned long stringCompare(char* p, char* t, unsigned int plength, unsigned int tlength)
    {
    char opt[OPERATIONCOUNT];

    unsigned long lowest_cost = 0;

    if(plength == 0)
        {
        return tlength * indel(' ');
        }

    if(tlength == 0)
        {
        return plength * indel(' ');
        }

    opt[MATCH] = stringCompare(p, t, plength - 1, tlength - 1) + match(p[plength - 1], t[tlength - 1]);
    opt[INSERT] = stringCompare(p, t, plength, tlength - 1) + indel(t[tlength - 1]);
    opt[DELETE] = stringCompare(p, t, plength -1, tlength) + indel(p[plength - 1]);


    lowest_cost = opt[MATCH];
    for(int k = INSERT; k <= DELETE; ++k)
        {
        if(opt[k] < lowest_cost)
            {
            lowest_cost = opt[k];
            }
        }

    return lowest_cost;
    }

int main()
    {
    string p;
    string t;

    cout << "Enter the pattern : " << endl;

    std::getline(std::cin, p);

    cout << "Pattern is : " << p << endl;

    cout << "Enter the text : " << endl;

    std::getline(std::cin, t);

    cout << "Text is : " << t << endl;

    cout << "Cost of conversion = " << stringCompare(const_cast<char*>(p.c_str()),
            const_cast<char*>(t.c_str()), p.size(), t.size()) << endl;

    return 0;
    }

