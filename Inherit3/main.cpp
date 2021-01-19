#include<iostream>
#include<iterator>

using namespace std;
//template <class T, int n> class My_Iterator
//{
//public:
//	My_Iterator();
//	~My_Iterator();
//
//private:
//
//};
//
//template <class T, int n> My_Iterator<T,n>::My_Iterator()
//{
//}
//
//template <class T, int n> My_Iterator<T,n>::~My_Iterator()
//{
//}

template <class T, int n> class My_Container
{
public:
	My_Container() { cout << "default constructor" << endl;  a = new T[n]; }//default constructor
	explicit My_Container(T* b) :My_Container() {//copy constructor that calls the default constructor
		cout << "1st copy constructor" << endl;
		for (size_t i = 0; i < n; ++i)
			a[i] = b[i];
	}
	My_Container(const My_Container& b) :My_Container() {//another copy constructor
		cout << "2nd copy constructor" << endl;
		for (size_t i = 0; i < n; i++)
			a[i] = b.a[i];
	}
	My_Container(My_Container&& b)noexcept {//move constructor
		cout << "move constructor" << endl;
		My_Container();//calling the default constructor
		a = b.a;
		b.a = nullptr;
	}
	My_Container(initializer_list<T> lst) :My_Container() {//initialization list constructor (calls the default one as well)
		cout << "constructor using initialization list" << endl;
		copy(lst.begin(), lst.end(), a);
	}
	class iterator;
	My_Container& operator=(My_Container&& b)noexcept;//move assignment
	My_Container& operator=(const My_Container& b);//copy assignment
	T& operator[](int index);//range unchecked access
	T& at(int index);//ranged checked access
	T size() const { return n; }//the current size of the vector
	void swap(My_Container& b);
	void print();
	void fill(T x);
	iterator begin() { return a; }
	iterator end() { return a + n; }
	~My_Container();

private:
	T* a;
};

template <class T, int n> My_Container<T,n>& My_Container<T,n>::operator=(My_Container&& b)noexcept{
	cout << "move assignment" << endl;
	if (this != &b){
		delete[] a;         // release the old resource
		a = b.a;   // acquire the new resource
		b.a = nullptr;
	}
	return *this;
}

template <class T, int n> My_Container<T, n>& My_Container<T, n>::operator=(const My_Container& b){
	cout << "copy assignment" << endl;
	T* c = new T[n];
	for (int i = 0; i < n; ++i)
		c[i] = b.a[i];
	delete[] a;
	a = c;
	return *this;
}

template <class T, int n> void My_Container<T,n>::swap(My_Container& b) {
	My_Container temp = move(b);
	b = move(*this);
	*this = move(temp);
}

template <class T, int n> void My_Container<T, n>::print() {
	if (a == nullptr) { 
		cout << "empty" << endl; 
		return; 
	}
	for (int i = 0; i < n; ++i)
		cout << a[i] << ",";
	cout << endl;
}

template <class T, int n> void My_Container<T, n>::fill(T x) {
	for (int i = 0; i < n; ++i)
		a[i] = x;
}

template <class T, int n> T& My_Container<T, n>::operator[](int index){
	return(a[index]);
}

template <class T, int n> T& My_Container<T, n>::at(int index) {
	if (index < 0 || index >= n)
		cout << "bad index!" << endl;
	return a[index];
}

template <class T, int n> My_Container<T,n>::~My_Container(){
	cout << "destructor" << endl;
	delete[] a;
}

template <class T, int n> class My_Container<T, n>::iterator {
	T* arr;
public:
	iterator(T* arr = nullptr) :arr(arr) {}
	bool operator==(const iterator& b) const { return arr == b.arr; }
	bool operator!=(const iterator& b) const { return arr != b.arr; }
	iterator& operator++() { ++arr; return *this; }
	iterator& operator--() { --arr; return *this; }
	ptrdiff_t operator-(const iterator& b) const { return arr - b.arr; }
	iterator& operator+=(int amount) { arr += amount; return *this; }
	iterator& operator-=(int amount) { arr -= amount; return *this; }
	bool operator<(const iterator& b) const { return arr < b.arr; }
	bool operator<=(const iterator& b) const { return arr <= b.arr; }
	bool operator>(const iterator& b) const { return arr > b.arr; }
	bool operator>=(const iterator& b) const { return arr >= b.arr; }
	T& operator[](int index) const { return *(arr + index); }
	T& operator*() const { return *arr; }

};

//template<class T, int n>
//class iterator_traits<My_Iterator<T, n> >
//{
//public:
//	using difference_type = std::ptrdiff_t;
//	using size_type = std::size_t;
//	using value_type = T;
//	using pointer = T* ;
//	using reference = T& ;
//	using iterator_category = std::random_access_iterator_tag;
//};

int main() {
	double data[10]{ 1,2,3,4,5,6,7,8,9,10 };
	My_Container<double, 5>  x;
	My_Container<double, 5>  y(data);
	//My_Container<double, 5>::iterator it = y.begin();
	//cout << y[0];
	My_Container<double, 5> z{ 6,7,8,9,10 };
	x[0] = y[0] + z[0];
	/*for (double* i = z.begin(); i < z.end(); i++)
		cout << *i ;*/
	for (size_t i = 0; i < z.size(); ++i)
		cout << z[i];
	cout << endl;
	//x.fill(2.0);
	//x.print();
	//y.print();

	//y.swap(x);  //move based swap
	//x.print();
	//y.print();
	//x = move(y);
	//x.print();
	//y.print();
	//cout << " one element in x is " << x[3] << endl;

	return 0;
}
