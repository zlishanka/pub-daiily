/*
 * C++ libraries provide implementations of smart pointers in following types:

auto_ptr
unique_ptr
shared_ptr
weak_ptr
They all are declared in a memory header file.

auto_ptr

This class template is deprecated as of C++11. unique_ptr is a new facility with a similar functionality, but with improved security.
*/ 

// C++ program to illustrate the use of auto_ptr
#include <iostream>
#include <memory>
using namespace std;

class A {
public:
	void show() { cout << "A::show()" << endl; }
};

int main()
{
	// p1 is an auto_ptr of type A
	auto_ptr<A> p1(new A);
	p1->show();

	// returns the memory address of p1
	cout << p1.get() << endl;

	// copy constructor called, this makes p1 empty.
	auto_ptr<A> p2(p1);
	p2->show();

	// p1 is empty now
	cout << p1.get() << endl;

	// p1 gets copied in p2
	cout << p2.get() << endl;

	return 0;
}

