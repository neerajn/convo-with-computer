/*
 * SolutionQ3.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: neeraj
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <list>

#include "SolutionQ3.h"

SolutionQ3* SolutionQ3::instance_ = NULL;
pthread_mutex_t SolutionQ3::tlock_;

SolutionQ3::SolutionQ3 () :
        splitSize_ (0),
        file_ (NULL)
{
}

SolutionQ3::~SolutionQ3 ()
{
}

void SolutionQ3::handleSignal (int signo)
{
    std::cout << "Got a term signal. terminating..." << std::endl;

    switch (signo)
    {
        case SIGINT:
            exit(0);
            break;
        default:
            break;
    }
}

/**
 * @Desc
 * Not meant to be thread safe. Only run by the main thread.
 * All threads are created hence forth.
 */
SolutionQ3& SolutionQ3::getInstance (void)
{
    if (NULL == instance_)
    {
        instance_ = new SolutionQ3();
    }

    return *instance_;
}

void SolutionQ3::dumpToFile (const char* file_, std::vector<struct record*>& data)
{
    char* filename = new char [100 * sizeof (char)];

    /*
    time_t t = time(0);   // get time now
    struct tm * now = localtime (&t);

    sprintf(filename, "%s%d%d%d%d%d%d", file_,(now->tm_year + 1900),
            (now->tm_mon + 1),
            now->tm_mday,
            now->tm_hour,
            now->tm_min,
            now->tm_sec);
     */

    struct timespec curr;
    double accum;

    if( clock_gettime( CLOCK_REALTIME, &curr) == -1 )
    {
      perror( "clock gettime" );
    }

    sprintf(filename, "%s%ld", file_, curr.tv_nsec);

    std::cout << "Filename: " << filename << std::endl;

/*
    for (std::vector<struct record*>::iterator it = data.begin();
                         it != data.end(); ++it)
    {

        struct record* r = *it;

        std::cout << r->type << std::endl;
        std::cout << r->symbol << std::endl;
        std::cout << r->price << std::endl;
        std::cout << r->quantity << std::endl;
        std::cout << r->expirydate << std::endl;
        std::cout << r->strikeprice << std::endl;
        std::cout << r->amendtime << std::endl;
        std::cout << r->id << std::endl;
        std::cout << r->parentid << std::endl;
    }
*/
    std::ofstream file;
    file.open (filename);

    if (file.good())
    {
        char buf[256 * sizeof(char)];

        for (std::vector<struct record*>::iterator it = data.begin();
                             it != data.end(); ++it)
        {
            memset (buf, 0, 256 * sizeof(char));

            struct record* r = *it;

            sprintf (buf, "%c~%s~%.2f~%.2f~%ld~%.2f~%ld~%ld~%ld\n",
                    r->type, r->symbol, r->price, r->quantity, r->expirydate,
                    r->strikeprice, r->amendtime, r->id, r->parentid);

            file << buf;
        }
    }

    file.close();

}

void SolutionQ3::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return;
}

bool SolutionQ3::run (int argc, char** argv)
{
    // validate the input
    if (!validate (argc, argv))
    {
        return false;
    }
    std::cout << "A" <<std::endl;

    // setup signal handling
    struct sigaction act;
    act.sa_handler = SolutionQ3::handleSignal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);

    // MULT 1000 2500
    std::map<std::string, std::vector<struct record*> > recordmap;
    std::ifstream is (file_);
    if (is)
    {
      // get length of file:
      is.seekg (0, is.end);
      int length = is.tellg();
      int parts = 1;
      is.seekg (0, is.beg);

      if (length > 1024)
      {
          parts = length / 1024;
      }
      else
      {
          parts = 1;
      }

      std::cout << "parts: " << parts <<std::endl;

      for (int i = 0; i < parts; ++i)
      {
          char* buffer = new char [1024];

          is.read (buffer, 1024);

          std::vector<std::string> lines;
          std::string buf (buffer);

          split (buf, '\n', lines);
          std::cout << "lines in part: " << lines.size() <<std::endl;

          for (int k = 0; k < lines.size(); ++k)
          {
              std::string line = lines[k];
              std::cout << line << std::endl;

              std::vector<std::string> tokens;

              split (line, '~', tokens);

              std::cout << "tokens in line: " << tokens.size() <<std::endl;

              if (tokens.size() < 9)
              {
                  continue;
              }

              struct record* r = new struct record;
/*
              for (int g = 0; g < tokens.size(); g++)
              {
                  std::cout << tokens[g] << std::endl;
              }
*/
              std::cout << tokens[0] << " is the type." << std::endl;
              r->type = tokens[0][0];
              memset (r->symbol, 0, sizeof(r->symbol) * sizeof(char));
              memcpy (r->symbol, tokens[1].c_str(), tokens[1].length() * sizeof(char));
              r->price  = atof (tokens[2].c_str());
              r->quantity = atof (tokens[3].c_str());
              r->expirydate = atoi (tokens[4].c_str());
              r->strikeprice = atof (tokens[5].c_str());
              r->amendtime = atol (tokens[6].c_str());
              r->id = atol (tokens[7].c_str());
              r->parentid = atol (tokens[8].c_str());

              bool newinsert = true;
              // std::cout << << std::endl;
              for (std::map<std::string, std::vector<struct record*> >::iterator it = recordmap.begin();
                      it != recordmap.end(); )
              {
                  std::cout << it->first << '\n';
                  if (it->first.compare(r->symbol) == 0)
                  {
                      std::cout << "split size is: " << splitSize_ << std::endl;
                      std::cout << "vector size is: " << it->second.size() << std::endl;

                      if (it->second.size() >= splitSize_)
                      {
                          std::cout << "dump" << std::endl;
                          dumpToFile (it->first.c_str(), it->second);

                          recordmap.erase (it);

                          newinsert = true;

                          break;
                      }
                      else
                      {
                          it->second.push_back(r);
                      }

                      std::cout << "append insert" << std::endl;

                      newinsert = false;

                      break;
                  }

                  ++it;
              }

              if (newinsert == true)
              {
                  std::cout << "New insert" << std::endl;

                  std::vector<struct record*>* vec = new std::vector<struct record*>();
                  vec->push_back (r);

                  recordmap[r->symbol] = *vec;
              }
          }
        }

      // dump rest
      std::cout << "dump all" << std::endl;
      for (std::map<std::string, std::vector<struct record*> >::iterator it = recordmap.begin();
              it != recordmap.end(); ++it)
      {
          dumpToFile (it->first.c_str(), it->second);
      }
    }

    //T~ICICIBANK~1000~100~20121210~120~20121209103030~1234~0
    return true;
}

bool SolutionQ3::validate(int argc, char** argv)
{
    if (3 != argc)
    {
        std::cout << "Error: invalid number of arguments." << std::endl;
        return false;
    }

    char* splitsize = argv[1];
    file_ = argv[2];

    int splitsizesize = strlen(splitsize);
    for (int i = 0; i < splitsizesize; ++i)
    {
        if (!isdigit(splitsize[i]))
        {
            std::cout << "Error: Invalid file split size. It must be a number."
                      << std::endl;

            return false;
        }
    }

    splitSize_ = atoi (splitsize);
    return true;
}
