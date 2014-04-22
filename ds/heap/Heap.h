/*
 * Heap.h
 *
 *  Created on: Apr 22, 2014
 *      Author: neerajnandakumar
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <math.h>

namespace convo
{

    template <int SIZE = 1000>
    class BinaryHeap
    {
        public:
            BinaryHeap ()
            {

            }

            ~BinaryHeap ()
            {

            }

            int left (int pos)
            {
                return data[(2 * pos) + 1];
            }

            int right (int pos)
            {
                return data[(2 *  pos) + 2];
            }

            int parent (int pos)
            {
                return floor ((pos - 1) / 2);
            }

            void heapify ()
            {

            }

        private:

            int data[SIZE];
    };

} /* namespace convo */

#endif /* HEAP_H_ */
