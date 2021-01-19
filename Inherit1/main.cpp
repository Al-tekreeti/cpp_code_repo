#include<iostream>

using namespace std;

class Student{
public:
	enum year{FRESH, SOPH, JUNIOR, SENIOR, GRAD};
	Student(char* nm, int id, double g, year x) :student_id(id), gpa(g), y(x) { copy_n(nm, 30, name); }
	virtual void print() const;
	~Student();

protected:
	int student_id;
	double gpa;
	year y;
	char name[30];
};

void Student::print() const{
	cout << name << "," << student_id << "," << y << "," << gpa << endl;
}

Student::~Student()
{
}

class Grad_Student:public Student{
public:
	enum support {TA, RA, FELLOWSHIP, OTHER};
	Grad_Student(char* nm, int id, double g, year x, support t, char* d, char* th):Student(nm, id, g, x), s(t){
		copy_n(d, 10, dept);
		copy_n(th, 80, thesis);}
	void print() const;
	~Grad_Student();

protected:
	support s;
	char dept[10];
	char thesis[80];

};
void Grad_Student::print() const{
	Student::print();
	cout << s << "," << dept << "," << thesis << endl;
}

Grad_Student::~Grad_Student(){
}

int main() {
	char name1[] = "Mae Pohl", name2[] = "Morris Pohl", deprt[] = "Pharmacy", desrt[] = "Retail Pharmacies";
	Student S(name1, 100, 3.425, Student::FRESH), *PS = &S;
	Grad_Student GS(name2, 200, 3.2564, Student::GRAD, Grad_Student::TA, deprt, desrt), *PGS;
	PS->print();//PS is of type Student and points at a Student object
	PS = PGS = &GS;// PS is of type Student but points at Grad_Student object
	PS->print();
	PGS->print();
	return 0;
}
