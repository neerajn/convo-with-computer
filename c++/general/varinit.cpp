#include <iostream>

struct AStruct
{
    int32_t a;
    char c;
    float f;
    double d;
};

class AClass
{
    AClass (int ac) : a (ac)
    {

    }

    int a;
};

int main (int argc, char* argv[])
{

    int i1 {1};
    int i2 {2.5}; // Compilation warning: no narrowing conversions allowed;
    int i3 = 1.5; // allowed here. implicit conversion

    AStruct t1 {1, 'a', 2.3, 4.5};
    AStruct t2 {1.5, 'a', 2.3, 4.5}; // Compilation warning: no narrowing conversions allowed;
    AStruct t3 {1, 658, 2.3, 4.5}; // Compilation warning: no narrowing conversions allowed;

    std::cout << i1 << std::endl;
    std::cout << i2 << std::endl;
    std::cout << i3 << std::endl;

    return 0;
}
