#include<iostream>
using namespace std; 

int main() {
    int n = 6; 
   
    //while (n++ <= 5) 
    //{  cout << n << ' '; }
    //++n; 
    
    int x = 0; 
    //x = --n;
    /* while (x < 5) {
        cout << x << " "; 
        x++;
    } */ 
    //cout << x << endl; 
    for (int count = 0; count < 3; count++) 
        x += count;
    cout << x << endl; 
}
