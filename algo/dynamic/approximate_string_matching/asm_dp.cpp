/*
 * asm_recursive.cpp
 *
 *  Created on: 09-Aug-2015
 *      Author: neerajnandakumar
 */

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

const unsigned int MATCH  = 0;
const unsigned int INSERT = 1;
const unsigned int DELETE = 2;

const unsigned int OPERATIONCOUNT = 3;

typedef struct CellItem
{
    int cost;
    int parent;

} Cell;

const unsigned int MAXCELLS = 35;

Cell table[MAXCELLS + 1][MAXCELLS + 1];

void printCostMatrix()
    {
    for(int i = 0; i < MAXCELLS; ++i)
        {
        for(int j = 0; j < MAXCELLS; ++j)
            {
            cout << table[i][j].cost << " ";
            }
        cout << endl;
        }
    }

void printParentMatrix()
    {
    for(int i = 0; i < MAXCELLS; ++i)
        {
        for(int j = 0; j < MAXCELLS; ++j)
            {
            cout << table[i][j].parent << " ";
            }
        cout << endl;
        }
    }

unsigned int match(char x, char y)
    {
    if(x == y)
        {
        return 0;
        }
    return 1;
    }

unsigned int indel(char x)
    {
    return 1;
    }

void rowInit(int i)
    {
    table[0][i].cost = i;

    if(i > 0)
        {
            table[0][i].parent = INSERT;
        }
    else
        {
        table[0][i].parent = -1;
        }
    }

void columnInit(int i)
    {
    table[i][0].cost = i;

    if(i > 0)
        {
        table[i][0].parent = DELETE;
        }
    else
        {
        table[i][0].parent = -1;
        }
    }

void goalCell(char* p, char* t, int* i, int* j)
    {
    *i = strlen(p) - 1;
    *j = strlen(t) - 1;
    }

void processMatch(char* p, char* t, int i, int j)
    {
    if(p[i] == t[j])
        {
        cout << "M ";
        }
    else
        {
        cout << "S ";
        }
    }

void processInsert(char* t, int j)
    {
    cout << "I ";
    }

void processDelete(char* p, int i)
    {
    cout << "D ";
    }

void printPath(char* p, char* t, int i, int j)
    {
    if(table[i][j].parent == -1)
        {
        return;
        }
    if(table[i][j].parent == MATCH)
        {
        printPath(p, t, i - 1, j - 1);
        processMatch(p, t, i, j);
        }
    else if(table[i][j].parent == INSERT)
        {
        printPath(p, t, i, j - 1);
        processInsert(p, i);
        }
    else if(table[i][j].parent == DELETE)
        {
        printPath(p, t, i - 1, j);
        processDelete(t, j);
        }
    }


unsigned long stringCompare(char* p, char* t)
    {
    char opt[OPERATIONCOUNT];

    for(int i = 0; i < MAXCELLS; ++i)
        {
        rowInit(i);
        columnInit(i);
        }

    int plength = strlen(p);
    int tlength = strlen(t);

    int i = 0;
    int j = 0;
    int k = 0;

    for(i = 1; i < plength; ++i)
        {
        for(j = 1; j < tlength; ++j)
            {
            opt[MATCH] = table[i - 1][j - 1].cost + match(p[i], t[j]);
            opt[INSERT] = table[i][j - 1].cost + indel(t[j]);
            opt[DELETE] = table[i - 1][j].cost + indel(p[i]);

            table[i][j].cost = opt[MATCH];
            table[i][j].parent = MATCH;
            for(int k = INSERT; k <= DELETE; ++k)
                {
                if(opt[k] < table[i][j].cost)
                    {
                        table[i][j].cost = opt[k];
                        table[i][j].parent = k;
                    }
                }

            printCostMatrix();
            cout << endl;
            //printParentMatrix();
            }
        }

    printCostMatrix();
    cout << endl;
    printParentMatrix();

    goalCell(p, t, &i, &j);

    printPath(p, t, i, j);

    return table[i][j].cost;
    }

int main()
    {
    string p;
    string t;

    cout << "Enter the pattern : " << endl;

    std::getline(std::cin, p);

    p = " " + p;
    cout << "Pattern is : " << p << endl;

    cout << "Enter the text : " << endl;

    std::getline(std::cin, t);

    t = " " + t;
    cout << "Text is : " << t << endl;

    cout << "Cost of conversion = " << stringCompare(const_cast<char*>(p.c_str()),
            const_cast<char*>(t.c_str())) << endl;

    return 0;
    }

