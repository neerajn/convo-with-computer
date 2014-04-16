/*
 * listnode.h
 *
 *  Created on: 15-Mar-2014
 *      Author: neeraj
 */

#ifndef LISTNODE_H_
#define LISTNODE_H_

    template <class T, uint64_t SIZE>
    struct Node
    {
        Node* next;
        T data;

        explicit Node (T& data) : next (nullptr), data (data) {}

        Node (Node* head, T& data) : next (head), data (data) {}
    };

    template <int T, uint64_t SIZE>
    struct IntNode : Node <T, SIZE>
    {
    };

    template <double T, uint64_t SIZE>
    struct DoubleNode : Node <T, SIZE>
    {
    };

    template <long T, uint64_t SIZE>
    struct LongNode : Node <T, SIZE>
    {
    };

#endif /* LISTNODE_H_ */
