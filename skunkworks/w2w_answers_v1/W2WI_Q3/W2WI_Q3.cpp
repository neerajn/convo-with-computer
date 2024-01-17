/*============================================================================
// Name        : W2WI_Q3.cpp
// Author      : neeraj
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================
 *
 *Consider a binary file each record of which can be defined as -
struct record {
  unsigned char type;
  cha symbol[50];
  double price;
  double quantity;
  long expirydate;
  double strikeprice;
  long amendtime;
  long id;
  long parentid;
};

  Sample records in textual format will look like below -
  type~symbol~price~quantity~expirydate~strikeprice~amendtime~id~parentid
  T~ICICIBANK~1000~100~20121210~120~20121209103030~1234~0
  T~AXISBANK~1000~100~20121210~120~20121209103031~1235~0
  T~SBIBANK~1000~100~20121210~120~20121209103032~1236~0
  P~ICICIBANK~1100~100~20121210~120~20121209103030~1237~1234
  P~AXISBANK~1000~100~20121210~120~20121209103031~1238~1235
  T~ICICIBANK~1000~100~20121210~120~20121209103035~1239~0
  T~CITIBANK~1000~101~20121210~120~20121209103036~1240~0
  P~ICICIBANK~1100~100~20121210~120~20121209103030~1241~1234
  P~ICICIBANK~1100~100~20121210~120~20121209103035~1242~1239

  The maximum number of records in this file can be to the scale of 500 million.
  You have to write a optimal C/C++ program to split the file into multiple files such that each smaller file contains at least X number of records, where X is an integer provided as an input.
  You have to take keep in mind below -
  1. A record in the file can be uniquely identified by the "id"
  2. For a symbol matching T and P records should be in the same smaller file. For eg. If the sample file above is splitted into files containing at least two rows each then records -
  T~ICICIBANK~1000~100~20121210~120~20121209103030~1234~0
  P~ICICIBANK~1100~100~20121210~120~20121209103030~1237~1234
  P~ICICIBANK~1100~100~20121210~120~20121209103030~1241~1234
  should be in one file.

  Your program should perform on following grounds -
  1. Good choice of data structures
  2. Optimal way of file I/O
  3. Time taken
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SolutionQ3.h"

int main(int argc, char** argv)
{
    // get a Solution instance
    SolutionQ3& soln = SolutionQ3::getInstance();

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
