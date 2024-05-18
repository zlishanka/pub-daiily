#include <iostream>
using namespace std;

int main() {
   int numRows;
   int numColumns;
   int currentRow;
   int currentColumn;
   char currentColumnLetter;

   cin >> numRows;
   cin >> numColumns;

   /* Your solution goes here  */
   for (currentRow = 1; currentRow <= numRows; currentRow++) {
       for (currentColumn = 0; currentColumn < numColumns; currentColumn++) {
           cout << currentRow << char(currentColumn + int('A')) << " ";
       }
   }
   cout << endl;

   return 0;
}
