/*
 * Heap.h
 *
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <math.h>
#include <string.h>
#include <stdlib.h>

namespace convo
{

#define MINHEAP 0
#define MAXHEAP 1

    template <int SIZE = 1000, bool MODE = MINHEAP>
    class BinaryHeap
    {
        public:
            BinaryHeap () : size (0)
            {
                memset ((void*)data, 0, sizeof (int) * SIZE);
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

            void insertItem (int value)
            {
                if (MODE)
                {
                    maxHeapify ();
                }
                else
                {
                    minHeapify ();
                }
                size ++;
            }

            void deleteItem ()
            {
                if (MODE)
                {
                    maxHeapify ();
                }
                else
                {
                    minHeapify ();
                }

                size --;
            }

            void print ()
            {

            }

            int getSize ()
            {
                return size;
            }

        private:

            void deleteMin ()
            {

            }

            void deleteMax ()
            {

            }

            void minHeapify ()
            {

            }

            void maxHeapify ()
            {

            }

        private:

            int data[SIZE];
            int size;

    };

} /* namespace convo */

#endif /* HEAP_H_ */
