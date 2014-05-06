
#include <iostream>
#include <thread>


void call_from_thread() {
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    //Launch a thread
    std::thread t1(call_from_thread);

    //Join the thread with the main thread
    t1.join();
    
    return 0;
}
