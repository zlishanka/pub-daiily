#include <iostream>
using namespace std;

int main() {
   int userNum;
   int i;
   int j;
   cout << "Please enter an integer value: ";
   cin  >> userNum;

   /* Your solution goes here  */
   for (i = 0; i <= userNum; i++) {
      for (j = 0; j < i; j++) 
          cout << " ";
      cout << j << endl; 
   } 
   return 0;
}
