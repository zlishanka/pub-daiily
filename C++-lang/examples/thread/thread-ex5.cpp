#include <future>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// std::mutex mu;
// std::condition_variable cond;

//pass result to main thread
// void factorial(int N, int& x) {
//int factorial(int N) {
//int factorial(std::future<int>& f) { 
int factorial(std::shared_future<int> f) { 
    int res = 1;
    int N = f.get();
    for (int i = N; i > 1; --i) {
        res *= i;
    }

    cout << "Result is: " << res << endl;
    //x = res;
    return res;
}

int main() {
    int x; 
    // std::thread t1(factorial, 4, std::ref(x));

    // t1.join();
    // async might create a thread
    //std::future<int> fu = std::async(std::launch::async, factorial, 4);
    // async wait the get() call to execute , won't create thread
    //std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
    // default

    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::shared_future<int> sf = f.share();

    // all child threads get the same value 
    std::future<int> fu = std::async(std::launch::async, factorial, sf);
    std::future<int> fu2 = std::async(std::launch::async, factorial, sf);
    std::future<int> fu3 = std::async(std::launch::async, factorial, sf);

    // do something else
    // wait until the async finish
    p.set_value(4);
   //x = fu.get();

    return 0;
}