#include <iostream>

class D {
public:
    void foo() {
        std::cout << "Foooooo" << std::endl;
    }
};


//class C:  public D {
class C:  virtual public D {
};

//class B:  public D {
class B:  virtual public D {
};

class A: public B, public C {
};

// If you don’t use virtual inheritance in this case, you will get two copies of D in class A: 
// one from B and one from C. To fix this you need to change the declarations of classes C and B to be virtual, as follows:
//
int main(int argc, const char * argv[]) {
    A a;
    a.foo();
}
