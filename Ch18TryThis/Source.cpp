#include <iostream>
#include <string>
#include <vector>


struct X
{
	int val;

	void out(const std::string& s, int nv)
	{
		std::cerr << this << "->" << s << ": " << val << " (" << nv << ")\n";
	}

	//default constructor
	X() { out("X()", 0); val = 0; }
	
	X(int v) { val = v; out("X(int)", v); }
	//copy constructor
	X(const X& x) { val = x.val; out("X(X&) ", x.val); }
	//copy assignment
	X& operator=(const X& a)
	{
		out("X::operator=()", a.val); val = a.val; return *this;
	}
	//destructor
	~X() { out("~X()", 0); }
};

//X glob(2);	//a global variable

X copy(X a) { return a; }

X copy2(X a) { X aa = a; return aa; }

X& ref_to(X& a) { return a; }

X* make(int i) { X a(i); return new X(a); }

struct XX { X a; X b; };

class vect {
	int sz; //size of vect
	double* elem; //a pointer to the elements

public:
	explicit vect(int s) //constructor (s is element count)
		:sz(s), elem{ new double[s] } //uninitialized memory for elements
	{
		for (int i = 0; i < sz; ++i) elem[i] = 0.0;	//initializes memory
	}


	double operator[](int n) { return elem[n]; }

	int size() const { return sz; }
	double get(int n) const { return elem[n]; }
	void set(int n, double v) { elem[n] = v; }


	~vect() { delete[] elem; }
};

int main()
{
	/*X loc{ 4 };
	X loc2{ loc };
	loc = X{ 5 };
	loc2 = copy(loc);
	loc2 = copy2(loc);
	X loc3{ 6 };
	X& r = ref_to(loc);
	delete make(7);
	delete make(8);

	std::vector<X> v(4);
	XX loc4;
	X* p = new X{ 9 };
	delete p;
	X* pp = new X[5];
	delete[] pp;*/

	vect test1(5);
	for (int i = 0; i < test1.size(); ++i)
		test1.set(i, 1.1 * i);

	std::cout << test1[2];
	//test1[2] = 3.3; //throws error, left operand must be l-value
	return 0;
}