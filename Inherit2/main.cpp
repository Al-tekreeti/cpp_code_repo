#include<iostream>

using namespace std;

class B
{
public:
	int i;
	virtual void print_i() const { cout << i << "inside B" << endl; }//try it without virtual
	B();
	~B();
};

B::B(){
}

B::~B(){
}

class D:public B
{
public:
	void print_i() const { cout << i << "inside D" << endl; }
	D();
	~D();
};

D::D()
{
}

D::~D()
{
}
int main() {
	B b;
	B* pb = &b;
	D f;
	f.i = 1 + (b.i = 1);
	pb->print_i();
	pb = &f;
	pb->print_i();
	return 0;
}
