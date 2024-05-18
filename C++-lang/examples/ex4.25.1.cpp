#include <iostream>
using namespace std;

int main() {

   /* Type your code here. */
   string str[100]; 
   int row = 0;
   int i = 0;
   int j = 0;
   while (1) {
       getline(cin, str[row]);
       if ((str[row].compare("quit") == 0) ||
         (str[row].compare("Quit") == 0)  ||
         (str[row].compare("q") == 0)) {
           break;
       } 
       ++row;
   } 
   for (i = 0; i < row; ++i) {
       for (j = str[i].length()-1; j >= 0; --j) {
               cout << str[i][j];
       }
       cout << endl;
   }
   return 0;
}
