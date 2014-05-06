/*
 * ConsolePrinter.h
 *
 *  Created on: 05-May-2014
 *      Author: neerajnandakumar
 */

#ifndef CONSOLEPRINTER_H_
#define CONSOLEPRINTER_H_

namespace convo
{

class ConsolePrinter
{
public:
    ConsolePrinter ()
    {

    }
    ~ConsolePrinter ()
    {

    }

    void process (bool result, std::string message)
    {
        std::cout << message << " " << result << std::endl;
    }
};

} /* namespace convo */

#endif /* CONSOLEPRINTER_H_ */
