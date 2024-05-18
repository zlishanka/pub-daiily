#include <iostream>
using namespace std;

int main() {

   /* Type your code here. */
   cout <<  "please input an integer:";
   int inNumber, outDigit;
   cin >> inNumber; 
   while (inNumber > 0) {
       outDigit = inNumber%10; 
       cout << outDigit;
       inNumber = inNumber / 10;
   }
   cout << endl;
   return 0;
}
