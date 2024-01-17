//
// Created by Neeraj Nandakumar on 20/10/2023.
//

#ifndef CONVO_WITH_COMPUTER_CREATEDELETEOBJECT_H
#define CONVO_WITH_COMPUTER_CREATEDELETEOBJECT_H

#include <iostream>

using namespace std;
class Test
{
public:
    Test()
    {
        cout << "Test created!" << endl;
    }

    ~Test()
    {
        cout << "Test destoyed!" << endl;
    }

    Test(const Test& other)
    {
        cout << "Test copy constructed" << endl;
    }

    Test& operator=(const Test& other)
    {
        cout << "Test copied" << endl;
        return *this;
    }

    void start(int i)
    {
        for (int j = 1; j <= i; ++j) {
            cout << j << endl;
        }
    }
};


#endif //CONVO_WITH_COMPUTER_CREATEDELETEOBJECT_H
