// CPP program without virtual destructor  
// causing undefined behavior 
#include<iostream> 
  
using namespace std; 
  
class base { 
  public: 
    base()      
    { cout<<"Constructing base \n"; } 
    virtual ~base() 
    { cout<<"Destructing base \n"; }      
}; 
  
class derived: public base { 
  public: 
    derived()      
    { cout<<"Constructing derived \n"; } 
    ~derived() 
    { cout<<"Destructing derived \n"; } 
}; 
  
int main(void) 
{ 
  cout <<" --- new a derived ---\n";
  derived *d = new derived();

  cout <<" --- delete a based pointed derived ---\n";
  base *b = d; 
  delete b; 

  getchar(); 
  return 0; 
} 
