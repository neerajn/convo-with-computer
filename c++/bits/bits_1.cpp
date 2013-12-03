#include <iostream>
#include <math.h>


void printBits (unsigned int a)
{

    int s = sizeof (a);
    for (int i = 0; i < s; i++)
    {
        int m = std::pow (2, i)
        std::cout << (a & m) << " " << std::endl;
    }
}

void whatBitsAreSet (unsigned int a)
{
    
}

void whatBitsAreNotSet (unsigned int a)
{


}

void setBit (unsigned int a, unsigned int pos)
{
    
}

unsigned int getBit (unsigned int a, unsigned int pos)
{
    
}

void setAllBits (unsigned int a)
{

}


int main (int argc, char* argv[])
{
    int i = 1;
    unsigned int u = 1;

    

    return 0;
}
