#include <iostream>


using namespace std;

void sizes(char ch, int i, int* p, bool b, double d, string s, char* cstr)
{
	cout << "The size of char is " << sizeof(char) << ' ' << sizeof(ch) << endl;
	cout << "The size of int is " << sizeof(int) << ' ' << sizeof(i) << endl;
	cout << "The size of int* is " << sizeof(int*) << ' ' << sizeof(p) << endl;

	cout << "The size of bool is " << sizeof(bool) << ' ' << sizeof(b) << endl;
	cout << "The size of double is " << sizeof(double) << ' ' << sizeof(d) << endl;
	cout << "The size of string is " << sizeof(string) << ' ' << sizeof(s) << endl;
	cout << "The size of char* is " << sizeof(char*) << ' ' << sizeof(cstr) << endl;


}

class A
{
public:
	A() { cout << "Class A constructor called\n"; }
	~A() { cout << "Class A destructor called\n"; }
};

struct B
{
	B() { cout << "Struct B constructor called\n"; }
	~B() { cout << "Struct B destructor called\n"; }
};

class C : public A
{
public:
	C() { cout << "Subclass C constructor called\n"; }
	~C() { cout << "Subclass C destructor called\n"; }
};
struct D : B
{
	D() { cout << "Substruct D constructor called\n"; }
	~D() { cout << "Substruct D destructor called\n"; }
};

void testCall()
{
	D dd;
	C cc;
}
int main()
{
	int* x = new int{ 20000 };
	char* cc = new char[]{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
	sizes('a', 1, x, true, 22.2, "What is up bruh", cc);


	A aa; B bb;
	testCall();
}