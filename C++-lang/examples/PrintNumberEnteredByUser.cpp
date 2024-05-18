#include <iostream>
#include <chrono>
#include <unistd.h> 
#include "StopWatch.h" 

using namespace std;

int main()
{    
    int number;
    StopWatch watch;  
    cout << "Enter an integer: ";
    cin >> number;

    cout << "You entered " << number << endl;    
      
    for (int i = 0; i < number; i ++) {
        watch.start(); 
        std::string time_now = "timeNow = " + watch.getCurrentTimestamp();  
        watch.stop(); 
        cout << time_now << " , time spent: " <<watch.getSeconds()*1000 << endl; 
        usleep(10000); 
    }
}
