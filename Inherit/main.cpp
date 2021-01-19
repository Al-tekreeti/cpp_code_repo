#include<iostream>

using namespace std;

template <class T> class Duo
{
public:
	Duo(T x = 0, T y = 0):first(x), second(y) {}
	void set_first(T d) { first = d; }
	void set_second(T d) { second = d; }
	T get_first() { return first; }
	T get_second() { return second; }
	~Duo();

protected:
	T first, second;
};

template <class T> Duo<T>::~Duo(){
}

template <class T> class Point:public Duo<T>{
public:
	virtual T length() { return static_cast<T>(sqrt(this->first*this->first + this->second * this->second)); }
	Point();
	Point(T x, T y = 0):Duo<T>(x,y){}
	~Point();

};

template <class T> Point<T>::Point(){
	Duo<T>();
}

template <class T> Point<T>::~Point(){
}

template <class T> class Point3d:public Point<T>{
public:
	Point3d():Point<T>(), z(0){}
	T length() { return static_cast<T>(sqrt(this->first*this->first + this->second * this->second + z*z)); }
	void set_z(T d) { z = d; }
	~Point3d();

private:
	T z;
};

template <class T> Point3d<T>::~Point3d(){
}

int main() {
	Point<double> q, r(3.0, 4.0);
	q.set_first(3.0);
	q.set_second(4.0);
	cout << q.get_first() << "," << q.get_second() << endl;
	cout << q.length();
	Point3d<double> t;
	t.set_first(5.0);
	t.set_second(6);
	t.set_z(7.0);
	cout << t.length() << endl;
	Point<double>* ptr_p = &t;
	cout << ptr_p->length() << endl;

	return 0;
}
