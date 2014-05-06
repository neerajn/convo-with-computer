/*
 * OperatorDefn.h
 *
 *  Created on: 05-May-2014
 *      Author: neerajnandakumar
 */

#ifndef OPERATORDEFN_H_
#define OPERATORDEFN_H_

#include <unordered_map>
#include <vector>



namespace convo
{

struct Action
{
    char operatorl;
    char targetChar;
};

class ActionList
{
    private:

        std::vector <Action> actionList;

    public:

        void add (char op, char t)
        {
            Action a;
            a.operatorl = op;
            a.targetChar = t;

            actionList.push_back (a);
        }

        std::vector <Action>getActionList ()
        {
            return actionList;
        }
};

}

#endif /* OPERATORDEFN_H_ */
