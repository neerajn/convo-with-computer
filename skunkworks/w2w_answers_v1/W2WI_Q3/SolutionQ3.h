/*
 * SolutionQ3.h
 *
 *  Created on: Apr 13, 2013
 *      Author: neeraj
 */

#ifndef SOLUTIONQ3_H_
#define SOLUTIONQ3_H_

#include <pthread.h>
#include <vector>


struct record
{
  unsigned char type;
  char symbol[50];
  double price;
  double quantity;
  long expirydate;
  double strikeprice;
  long amendtime;
  long id;
  long parentid;
};

class SolutionQ3
{
    public:

        ~SolutionQ3 ();

        static  SolutionQ3&     getInstance    (void);
        bool                    run              (int argc, char** argv);
        bool                    validate        (int argc, char** argv);

    private:

        SolutionQ3 ();
        SolutionQ3 (const SolutionQ3&);
        SolutionQ3& operator= (const SolutionQ3&);
        void split(const std::string &s, char delim, std::vector<std::string> &elems);
        static void            handleSignal   (int signo);
        void dumpToFile (const char* file_, std::vector<struct record*>& data);

        static SolutionQ3* instance_;
        static pthread_mutex_t tlock_;
        unsigned int splitSize_;
        char* file_;


};

#endif /* SOLUTIONQ3_H_ */
