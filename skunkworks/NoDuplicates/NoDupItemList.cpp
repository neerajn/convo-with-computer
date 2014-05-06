/*
 * NoDupItemList.cpp
 *
 *  Created on: 05-May-2014
 *      Author: neerajnandakumar
 */

#include "NoDupItemList.h"

using namespace convo;

int main (int argc, char* argv [])
{
    NoDupItemList list;

    list.add ("Tejas");
    list.add ("Vikas"); list.print ();
    list.add ("Neeraj"); list.print ();
    list.add ("Vikas"); list.print ();
    list.add ("Manohar"); list.print ();
    list.add ("Abhijit"); list.print ();
    list.add ("Dhruv"); list.print ();
    list.add ("Vikas"); list.print ();
    list.add ("Vikas"); list.print ();
    list.add ("Abhijit"); list.print ();
    list.add ("Tejas"); list.print ();
    list.add ("Abhijit"); list.print ();
    list.add ("Abhijit"); list.print ();
    list.add ("Vikram");

    list.print ();

    return 0;
}

