
/*
 * std::unique_ptr was developed in C++11 as a replacement for std::auto_ptr.
unique_ptr is a new facility with similar functionality, but with improved security (no fake copy assignments), added features (deleters) and support for arrays. It is a container for raw pointers. It explicitly prevents copying of its contained pointer as would happen with normal assignment i.e. it allows exactly one owner of the underlying pointer.
So, when using unique_ptr there can only be at most one unique_ptr at any one resource and when that unique_ptr is destroyed, the resource is automatically claimed. Also, since there can only be one unique_ptr to any resource, so any attempt to make a copy of unique_ptr will cause a compile-time error.
*/
// C++ program to illustrate the use of unique_ptr 
#include <iostream> 
#include <memory> 
using namespace std; 
  
class A { 
public: 
    void show() 
    { 
        cout << "A::show()" << endl; 
    } 
}; 
  
int main() 
{ 
    unique_ptr<A> p1(new A); 
    p1->show(); 
  
    // returns the memory address of p1 
    cout << p1.get() << endl; 
  
    // transfers ownership to p2 
    unique_ptr<A> p2 = move(p1); 
    p2->show(); 
    cout << p1.get() << endl; 
    cout << p2.get() << endl; 
  
    // transfers ownership to p3 
    unique_ptr<A> p3 = move(p2); 
    p3->show(); 
    cout << p1.get() << endl; 
    cout << p2.get() << endl; 
    cout << p3.get() << endl; 
  
    return 0; 
} 
