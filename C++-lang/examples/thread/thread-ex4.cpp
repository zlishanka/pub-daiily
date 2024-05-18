#include <thread>
#include <iostream>
#include <mutex>
#include <deque>

using namespace std;

std::deque<int> q;
std::mutex mu;
std::condition_variable cond; 

// producer of data
void function_1() {
    int count = 10;
    while (count > 0) {
        // busy waiting
        std::unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        cond.notify_one();  // notify one waiting thread, if there is one
        std::this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}

// consumer 
void function_2() {
    int data = 0;
    while (data != 1) {
        std::unique_lock<mutex> locker(mu);
        // if (!q.empty()) {
        cond.wait(locker, []() {return !q.empty();});   // spurious wake
            data = q.back();
            q.pop_back();
            locker.unlock();
            cout <<"t2 got a vlue from t1: "<< data << endl;
        // } else {
        //     locker.unlock();
        //     std::this_thread::sleep_for(chrono::microseconds(10));
        // }
    }
}

int main() {
    thread t1(function_1);
    thread t2(function_2);
    t1.join();
    t2.join();

    return 0;
}
