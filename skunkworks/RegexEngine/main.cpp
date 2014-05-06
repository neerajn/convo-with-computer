/*
 * main.cpp
 *
 *  Created on: 05-May-2014
 *      Author: neerajnandakumar
 */

#include <iostream>

#include "ConsoleReader.h"
#include "SimpleRegexEngine.h"
#include "ConsolePrinter.h"

void printHelp ()
{


}

int main (int argc, char* argv [])
{
    try
    {
        std::cout << "Starting regex engine. CTRL-C to exit." << std::endl;

        convo::ConsoleReader <convo::SimpleRegexEngine <convo::ConsolePrinter> > processor;

        processor.process ();
    }
    catch (...)
    {
        std::cout << "Unknown exception caught!" << std::endl;
    }

    return 0;
}


