/**
 *
 *
 */

#include <atomics>
#include <threads>
#include <stdint.h>

#define SIZE 100000

template <class ItemType>
class QItem
{
	public:
	
		void setValue (ItemType& item)
		{
			m_value = item;
			m_state.load = true;
		}
		
		ItemType getValue (void)
		{
			ItemType t = m_value;
			m_state = false;
			return t;
		}
	
	private:
		ItemType m_value;
		
		std::atomic<bool> m_state; // 0 == writable and 1 == readable
		// so the writer will set the value as readable post write and
		// reader will set the value as writable post read.
};

template <class ItemType, uint64_t QSIZE>
class Q
{
    public:
		Q (): m_index (1), m_itemHead(0)
		{
			m_itemHead = new char [QSIZE * sizeof (ItemType)];
		}

        /* function to enqueue */
		void enqueue (ItemType& item)
		{
			uint64_t index = m_index.load();
			m_itemHead[index].setValue (item);
		}

        /* function to dequeue */
		ItemType& dequeue (void)
		{
			
		}

        /* get the size of the queue */
		uint64_t getSize ()
		{
			
		}

    private:

    	/**/
		std::atomic<uint64_t> m_index;
		
		ItemType* m_itemHead;
};

int main (int argc, char* argv[])
{
   

}
