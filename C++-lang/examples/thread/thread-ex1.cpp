#include <iostream>
#include <thread>

using namespace std;

void function_1() {
    std::cout << "Beauty is only skin-deep" << std::endl;
}

int  main() {
    std::thread t1(function_1); // t1 starts running
    // t1.join();  // main thread wait for t1 to finish
    // t1.detach(); // t1 runs freely on its own, once deteched cannot be joined again

    // if (t1.joinable()) { // check if t1 is joinable
    //     t1.join();
    // }
    try {
        for (int i = 0; i < 100; ++i) {
            cout << "from main: " << i << endl;
        }
    } catch (...) {
        t1.join();
        throw;
    }
    t1.join();

    return 0;
}