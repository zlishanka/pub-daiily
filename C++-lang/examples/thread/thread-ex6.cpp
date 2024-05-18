#include <iostream>
#include <thread>
#include <future>
using namespace std;

class A {
    public:
    void f(int x, char c) {}
    long g(double x) { return 0;}
    int operator() (int N) {return 0;}
};

void foo(int x) {}

int main() {
    A a;

    // callable object
    std::thread t1(a, 6); // copy of a() in a different thread
    std::thread t2(std::ref(a), 6);     // a() in a different thread
    std::thread t3(A(), 6); //temp A;

    std::thread t4([](int x) {return x*x;}, 6); // lambda function
    std::thread t5(foo, 7);

    std::thread t6(&A::f, a, 8, 'W'); // copy_of_a.f(8, 'w') in different thread
    std::thread t7(&A::f, &a, 8, 'W'); // a.f(8, 'W') in different thread

    // std::async(std::launch::async, a, 6);
    // std::bind(a, 6);
    // std::call_once(once_flag, a, 6);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join(); 
    
    return 0;
}