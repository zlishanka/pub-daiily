#include <iostream>
#include <fstream>
#include <thread>
#include <string> 
#include <mutex>
using namespace std;

std::mutex mtx;

class LogFile {
    std::mutex m_mutex;
    std::ofstream f;
public:
    LogFile() {
        f.open("log.txt");
    }  
    // ~logFile() {
    //     f.close();
    // }
    void shared_print(string id, int value) {
        std::lock_guard<std::mutex> lck (m_mutex);
        f << "From " << id << ": " << value << endl;
    }
};


void function_1(LogFile& log) {
    for (int i = 0; i > -100; --i) {
        log.shared_print("From t1: ", i);
    }
}

int main() {
    LogFile log;
    std::thread t1(function_1, std::ref(log));

    for (int i=0; i < 100; ++i) {
        log.shared_print("From main: ", i);
    }

    t1.join();

    return 0;
}
