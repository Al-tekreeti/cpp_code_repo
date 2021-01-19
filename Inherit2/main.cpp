#include<iostream>

using namespace std;

class B
{
public:
	inline virtual void foo(int i) { cout << i << "inside B" << endl; }
	inline virtual void foo(double d) { cout << d << "inside B" << endl; }
	B();
	~B();

private:

};

B::B()
{
}

B::~B()
{
}

class D:public B
{
public:
	inline void foo(int i){ cout << i << "inside D" << endl; }
	D();
	~D();

private:

};

D::D()
{
}

D::~D()
{
}

int main() {
	D d;
	B b, *pb = &d;
	b.foo(9.5);
	d.foo(9.5);
	pb->foo(9.5);
	return 0;
}
