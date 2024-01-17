/**
 * Name        : W2WI_Q1.cpp
 * Author      : neeraj
 * Version     : 1
 * Copyright   :
 * Description :
 * Write a program which takes three inputs (command line)

    1. A string
    2. charcount (integer)
    3. threadcount - no of Threads(integer).

   Each thread then should start printing the chars in the string sequentially in the following format:

    eg:
    > myprinter ABCDEFGHIJ 3 4

    outPut:
    Using 4 threads to print ABCDEFGHIJ alternatively in set of 3 chars

    Thread1: ABC
    Thread2: DEF
    Thread3: GHI
    Thread4: JAB
    Thread1: CDE
    Thread2: FGH
    Thread3: IJA
    ......


    Your program output should strictly adhere to the above output apart from that it should perform well on following grounds -
    1. Good synchronization technique (starvation free)
 */

#include <iostream>

#include "SolutionQ1.h"

using namespace std;

int main(int argc, char** argv)
{
    // get a Solution instance
    SolutionQ1& soln = SolutionQ1::getInstance();

    // pass on the work and run
    try
    {
        soln.run(argc, argv);
    }
    // handle all exceptions
    catch(...)
    {
        std::cout << "encountered an unexpected exception. dying...." << std::endl;
    }

  return 0;
}
