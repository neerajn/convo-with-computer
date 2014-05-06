/*
 * FileReader.h
 *
 *  Created on: 05-May-2014
 *      Author: neerajnandakumar
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <iostream>
#include <string>

namespace convo
{

template <class Target>
class ConsoleReader : public Target
{
public:
    ConsoleReader ()
    {

    }
    ~ConsoleReader ()
    {

    }

    void process ()
    {
        while (true)
        {
            std::string regex;
            std::string target;
            std::cout << "Enter a regex: " << std::endl;
            std::cin >> regex;
            std::cout << "Enter a target string: " << std::endl;
            std::cin >> target;

            Target::process (regex, target);
        }
    }
};

} /* namespace convo */

#endif /* FILEREADER_H_ */
