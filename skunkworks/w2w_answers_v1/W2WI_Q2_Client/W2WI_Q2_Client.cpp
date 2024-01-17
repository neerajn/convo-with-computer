/**
 * Name        : W2WI_Q2_Client.cpp
 * Author      : neeraj
 * Version     : 1
 * Copyright   :
 * Description :
 * C, C++ Client-Server program with job scheduler:
   There are N number of jobs (see below the definition and example of a job).
   X number of clients will execute these N jobs and a server schedules them.
   Each job takes variable amount of time and the execution time is known only after the job is done.
   Design a system to get the jobs done in least amount of time. Communication is only between server and client, and they communicate over socket.

   Details of job:
   job is a command with data that need to be executed.
   job format:  <string:command><space><integer><space><integer>
   job commands: MULT, POW, ADD, SUB, XOR
   e.g:
   "MULT 1000 2500" // this is a job to multiply 1000 and 2500
   "POW 100 8"      // compute the power
   "ADD 100 200"    // addition
   "SUB 200 100"    // Subtract
   "XOR 10 10"      // do a bitwise xor

   Your program should perform on following grounds -
    1. Good handling of connection
    2. The design should scale without much change when new commands (lets us MODULO) are added
    3. Scheduling algorithm
 */

#include <iostream>

#include "SolutionQ2Client.h"

using namespace std;

int main(int argc, char** argv)
{
    // get a Solution instance
    SolutionQ2Client& soln = SolutionQ2Client::getInstance();

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
