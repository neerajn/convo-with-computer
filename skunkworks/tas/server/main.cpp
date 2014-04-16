
#include <iostream>

#include "server.h"

int main (int argc, char* argv [])
{

    if (argc != 3)
    {
        std::cout << "Usage: server 127.0.0.1 23451" << std::endl;
        return 1;
    }

    //validate IP argv[1]
    //validate port argv[2]

    Server server;

    server.startEngine (argv[1], atoi (argv[2]));

    return 0;
}
