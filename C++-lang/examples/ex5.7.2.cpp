#include <iostream>
#include <vector>
using namespace std;

int main() {
   vector<int> countDown(0);
   int newSize;
   unsigned int i;
   int total = 0; 
   cin >> newSize;

   /* Your solution goes here  */
   countDown.resize(newSize);
   //cout << countDown.at(0) << countDown.at(1) << countDown.at(2) << endl; 
   //return 0; 
   
   for (i = countDown.size() -1 ; i >= 0; i--, total++) {
      countDown.at(i) = i+1;
   }

   for (i = 0; i < countDown.size(); ++i) {
      cout << countDown.at(i) << " ";
   }
   cout << "Go!" << endl;

   return 0;
}
