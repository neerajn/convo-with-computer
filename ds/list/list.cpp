
#include <iostream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++11-extensions"
template<typename T> struct LinkedListNode
{
    T val;
    LinkedListNode<T>* next;
    LinkedListNode<T>* prev;
public:
    explicit LinkedListNode(T val): val (val), next(nullptr), prev(nullptr) {}
};

void appendNode(LinkedListNode<int>* prevNode,
                LinkedListNode<int>* node) {
    prevNode->next = node;
    node->prev = prevNode;
}

int main() {
    // Write your code here
    // Try creating 1 <-> 2 <-> 3
    // Test with cout
    int n = 10;
    auto prevNode = new LinkedListNode<int>(1);
    LinkedListNode<int>* head = prevNode;
    LinkedListNode<int>* tail = nullptr;
    for (int i = 2; i <= n; ++i) {
        auto lln = new LinkedListNode<int>(i);
        appendNode(prevNode, lln);
        prevNode = lln;
    }
    tail = prevNode;
    std::cout << "Print Forward" << std::endl;
    for (LinkedListNode<int>* iter = head; iter != nullptr; iter = iter->next) {
        std::cout << iter->val << std::endl;
    }
    std::cout << "Print Backward" << std::endl;
    for (LinkedListNode<int>* iter = tail; iter != nullptr; iter = iter->prev) {
        std::cout << iter->val << std::endl;
    }
}
#pragma clang diagnostic pop