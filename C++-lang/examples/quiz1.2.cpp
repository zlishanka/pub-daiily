#include<iostream>
#include <vector> 
using namespace std; 

int main() { 
    int arraySize = 5;
    //int a[arraySize] = {0, 0}; 
    int a[5] ;  
    int grades[] = {100, 90, 99, 80};
    for (int i = 0; i < arraySize; i++) {
        cout << a[i] << ' ';
    }
    char sentence[] = "I have a dream!";
    
    cout << endl; 
    cout << sizeof(grades) << endl; 
    cout << sizeof(grades[0]) << endl;
    cout << sizeof(grades)/sizeof(grades[0]) << endl; 
    int sizeA = sizeof(sentence)/sizeof(sentence[0]);
    for (int i = 0; i <= sizeA; i++) {
        cout << sentence[i] << ' '; 
    }
    cout << endl; 
    //int numbers[] = {99,87,67,55,101}; 
    int numbers[4] = {99,87}; 
    //for (int i = 1; i < 4; i++) 
    //    cout << numbers[i] << " ";  
    cout << numbers[3] << endl; 
    cout << endl;  

    const int SIZE = 5; 
    double x[SIZE]; 
    for (int i = 2; i <= SIZE; i++) { 
        x[i] = 0.0;
        cout << i << ' ' << x[i] << endl; 
    } 
    //x[5] = 0.0;  
    //vector<int> n = {10, 20};  
    vector<int> v(10, 2); 
    //cout << v << endl; 
    for(size_t i=0; i<v.size(); ++i)
        cout << v[i] << '\n'; 

    vector<int> b {3,5}; 
    for (int val : numbers)
        cout << val << endl; 

    return 0; 
}
