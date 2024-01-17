//
// Created by Neeraj Nandakumar on 20/10/2023.
//
#include <iostream>

#include "createdeleteobject.h"

using namespace std;

int main()
{
    cout << "Hello, World!" << endl;

    Test m1;

    Test m2 = m1;

    m1 = m2;

    Test* m3 = new Test();

    m3->start(5);

    delete m3;

    m3 = nullptr;

    unique_ptr<Test> m4(new Test());

    return 0;
}