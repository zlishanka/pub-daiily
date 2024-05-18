#include <iostream>
#include <thread>

using namespace std;

class Fctor {
    public:
        void operator()(string& msg) {
            cout << "t1 says: " << msg << endl;
            msg = "Trust is the mother of deceit.";
        }
};

// void func1(string& msg) {
//     cout << "t1 says: " << msg << endl;
//     msg = "Trust is the mother of deceit.";
// }

int main() {
    string s  = "Where there is no trust, there is no love";
     std::thread t1((Fctor()), std::ref(s)); // t1 starts running
    // std::thread t1((Fctor()), std::move(s));
    t1.join();
    cout << "from main: " << s << endl;
    cout << "number of threads can be run: " << std::thread::hardware_concurrency() << endl;
    return 0;
}