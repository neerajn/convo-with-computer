#include <iostream>

#include "simpleclient.h"

int main (int argc, char* argv [])
{

    if (argc != 3)
    {
        std::cout << "Usage: client 127.0.0.1 23451" << std::endl;
        return 1;
    }

    //TODO: validate IP argv[1]
    //TODO: validate port argv[2]

    SimpleClient client;

    client.start (argv[1], atoi (argv[2]));

    return 0;
}

