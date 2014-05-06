/*
 * SimpleRegexEngine.h
 *
 *  Created on: 05-May-2014
 *      Author: neerajnandakumar
 */

#ifndef SIMPLEREGEXENGINE_H_
#define SIMPLEREGEXENGINE_H_

#include <string.h>

#include "OperatorDefn.h"

namespace convo
{

template <class Target>
class SimpleRegexEngine : public Target
{
public:
    SimpleRegexEngine ()
    {
        //operators.load ();
    }

    ~SimpleRegexEngine ()
    {

    }
    //OperatorDefinition operators;

private:


    bool checkRegex (std::string& regex)
    {
        if (regex.size () == 0)
        {
            return false;
        }

        return true;
    }

    bool parseRegex (std::string& regex)
    {
        char* regexp = (char*) regex.c_str ();

        if (regexp[0] == '^' && !(regex.size () < 2))
        {
            alist.add ('^', regexp[1]);
        }

        if (regexp[regex.size() - 1] == '$' && !(regex.size () < 2))
        {
            alist.add ('$', regexp[regex.size() - 2]);
        }

        return true;
    }

    bool findMatch (std::string& regex, std::string& target)
    {
        std::cout << "finding match for " << target << " with " << regex << std::endl;
        int targetsize = target.size ();
        int regexsize = regex.size ();
        char* targetp = (char*) target.c_str ();
        char* regexp = (char*) regex.c_str ();

        if (!parseRegex (regex))
        {
            return false;
        }

        for (std::vector <Action>::iterator iter = alist.getActionList ().begin ();
                iter != alist.getActionList ().end (); ++iter)
        {
            if (((Action)*iter).operatorl == '^')
            {
                return targetp[0] == ((Action)*iter).targetChar;
            }

            if (((Action)*iter).operatorl == '$')
            {
                return targetp[target.size () - 1] == ((Action)*iter).targetChar;
            }


        }

        return true;
    }

    ActionList alist;

public:

    void process (std::string& regex, std::string& target)
    {
        if (!checkRegex (regex))
        {
            Target::process (false, "Invalid regex");
            return;
        }

        if (findMatch (regex, target))
        {
            Target::process (true, "Match found");
        }
        else
        {
            Target::process (false, "Match not found");
        }
    }
};

} /* namespace convo */

#endif /* SIMPLEREGEXENGINE_H_ */
