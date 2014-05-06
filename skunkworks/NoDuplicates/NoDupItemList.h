/*
 * NoDupItemList.h
 *
 *  Created on: 05-May-2014
 *      Author: neerajnandakumar
 */

#ifndef NODUPITEMLIST_H_
#define NODUPITEMLIST_H_

#include <list>
#include <unordered_map>
#include <string>
#include <iostream>

namespace convo
{

struct Node
{
    std::string m_name;
};

class NoDupItemList
{
public:
    NoDupItemList ()
    {

    }

    ~NoDupItemList ()
    {
        for (auto& iter : m_map)
        {
            delete iter.second;
        }
    }

    void add (std::string item)
    {
        Node* nodeItem = m_map[item];

        if (nodeItem == NULL)
        {
            Node* node = new Node;
            node->m_name = item;

            m_map[item] = node;
            m_list.push_back (node);
        }
        else
        {
            m_list.remove (nodeItem);
        }
    }

    void print ()
    {
        for (auto& iter : m_list)
        {
            std::cout << iter->m_name << std::endl;
        }
        std::cout << std::endl;
    }

private:

    std::unordered_map <std::string, Node*> m_map;
    std::list<Node*> m_list;
};
}

#endif /* NODUPITEMLIST_H_ */
