#include <iostream>
#include <vector>

using namespace std;
//exercise 1
template<typename T> void f(vector<T>& v1, vector<T> v2)
{
	if (v1.size() > v2.size()) v2.resize(v1.size());
	
	for (int i = 0; i < v1.size(); ++i)
		v1[i] += v2[i];
}
//exercise 2
template<typename T, typename U> T SumVec(const vector<T>& vt, const vector<U>& vu)
{
	if (vt.size() != vu.size()) throw runtime_error("Invalid vector sizes");
	T sum = 0;
	for (int i = 0; i < vt.size(); ++i)
		sum += vt[i] * vu[i];

	return sum;
}
//exercise 3
template<typename T, typename U> class Pair1 {
public:
	T t;
	U u;

	Pair1(T tt, U uu) : t(tt), u(uu) {}
};

template<typename T, typename U> 
ostream& operator<<(ostream& os, Pair1<T,U> p1)
{
	os << p1.t << ": " << p1.u << endl;
	return os;
}
//exercise 5
class Int
{
private:
	int i = 0;

public:
	Int() {}
	Int(int ii) :i(ii) {}

	int get() { return i; }
	const int get() const { return i; }

	void set(int ii) { i = ii; }

	int operator+(Int ii) { return i + ii.i; }
	int operator-(Int ii) { return i - ii.i; }
	int operator*(Int ii) { return i * ii.i; }
	int operator/(Int ii) { return i / ii.i; }

};

ostream& operator<<(ostream& os, const Int& i)
{
	return os << i.get();
}

istream& operator>>(istream& is, Int& i)
{
	int ii;
	if (is >> ii) i.set(ii);
	return is;
}
//exercise 6,7
template<typename T> class Number {
private:
	T num;
public:
	Number() : num(0) {}
	Number(T t) : num(t) {}

	T get() { return num; }
	const T get() const { return num; }

	void set(T t) { num = 2; }

	T operator+(Number<T> t) {return num + t.num;}
	T operator-(Number<T> t) { return num - t.num; }
	T operator*(Number<T> t) { return num * t.num; }
	T operator/(Number<T> t) { return num / t.num; }
	T operator%(Number<T> t) { return num % t.num; }
};

template<typename T>
ostream& operator<<(ostream& os, const Number<T> n)
{
	return os << n.get();
}

template<typename T>
istream& operator>>(istream& is, Number<T>& n)
{
	Number<T> nn;
	if (is >> nn) n.set(nn);
	return is;
}
int main()
{
	//exercise 1
	vector<int> vi1{ 1,2,3,4,5,6,7,8,9,10 };
	vector<int> vi2{ 16,17,18,19,20,21,22,23,24,25 };

	f(vi1, vi2);
	for (int i : vi1)
		cout << i << " ";
	cout << endl;

	vector<double> vd1{ 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.1 };
	vector<double> vd2{ 11.1, 22.2, 33.3, 44.4, 55.5, 66.6, 77.7, 88.8, 99.9, 100.1 };
	f(vd1, vd2);
	for (double d : vd1)
		cout << d << " ";
	cout << endl;
	//exercise 2
	cout << SumVec(vi2, vd2) << endl;
	cout << SumVec(vi1, vd1) << endl;
	/*//exercise 3
	vector<Pair1<char, string>> p;
	while (true)
	{
		cout << "Input a symbol followed by it's meaning:\nInput || to exit\n";
		char c;
		string s;
		if (cin >> c >> s) p.push_back(Pair1<char,string>(c, s));
		if (c == '|') break;
	}

	for (int i = 0; i < p.size(); ++i)
		cout << p[i];*/

	//exercise 5
	Int i;
	cout << "Input a desired integer:\n";
	cin >> i;
	cout << "Your desired integer was: " << i << endl;
	int i2(69);
	cout << i + i2 << endl
		<< i - i2 << endl
		<< i * i2 << endl
		<< i / i2 << endl;

	//exercise 6,7
	Number<int> ni1(15);
	Number<int> ni2(20);
	Number<double> nd1(5.5);
	Number<double> nd2(4.4);
	cout << "Custom Number operations: Integer\n";
	cout << ni1 + ni2 << endl
		<< ni1 - ni2 << endl
		<< ni1 / ni2 << endl
		<< ni1 * ni2 << endl
		<< ni1 % ni2 << endl;
	cout << "Custom Number operations: Double\n";
	cout << nd1 + nd2 << endl
		<< nd1 - nd2 << endl
		<< nd1 / nd2 << endl
		<< nd1 * nd2 << endl;
		//cout << nd1 % nd2 << endl; //produces error from using modulus with double types




	return 0;
}
