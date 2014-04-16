/**
 * Main class. All starts here
 *
 */
#include <iostream>

#include "server.h"

int main (int argc, char* argv [])
{

    if (argc != 2)
    {
        std::cout << "Usage: server 23451" << std::endl;
        return 1;
    }

    //validate port argv[2]

    Server server;

    server.startEngine (atoi (argv[1]));

    return 0;
}
