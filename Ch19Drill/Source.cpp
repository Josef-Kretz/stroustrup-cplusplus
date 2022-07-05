//chapter 19 drill
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T> ostream& operator<<(ostream& os, const vector<T>& t)
{
	for (int i = 0; i < t.size(); ++i)
		os << t[i] << " ";
	os << endl;

	return os;
}

template<typename T> istream& operator>>(istream& is, vector<T>& t)
{
	T tv;
	while (cin >> tv)
	{
		t.push_back(tv);
	}
	if (t.size() > 0) cin.clear();

	return is;
}

template<typename T> struct S {
private:
	T val; 

public:
	S(): val(T()) {}
	S(T t): val(t) {}

	const T& get() const;
	T& get();

	void set(T t);

	void operator=(const T& t);

	void read_val(T& v);
};

template<typename T> T& S<T>::get()
{
	return val;
}

template<typename T> const T& S<T>::get() const
{
	return &val;
}

template<typename T> void S<T>::set(T t) { val = t; }

template<typename T> void S<T>::operator=(const T& t)
{
	val = t;
}
template<typename T> void S<T>::read_val(T& v)
{
	if (cin >> v) val = v;
}



int main()
{
	S<int> s_int(5);
	S<char> s_char('a');
	S<double> s_d(1.110);
	S<string> s_str("Hello people!");

	S<vector<int>> s_v(vector<int> {1, 2, 3});

	cout << s_int.get() << " " << s_char.get() << " " << s_d.get() << " " << s_str.get() << " " << s_v.get()[0] << endl;

	s_int.set(100);
	s_char.set('C');
	s_d.set(100.100001);
	s_str.set("Freaky peeps");
	s_v.set(vector<int> {1001});


	cout << s_int.get() << " " << s_char.get() << " " << s_d.get() << " " << s_str.get() << " " << s_v.get()[0] << endl;

	s_int = 900;
	s_char = 'D';
	s_d = 900000000000;
	s_str = "Boomshakalackah";
	s_v = vector<int>{ 90101001 };

	cout << s_int.get() << " " << s_char.get() << " " << s_d.get() << " " << s_str.get() << " " << s_v.get()[0] << endl;

	/*int i = 0;
	string s;
	double d = 0.0;
	char c = '\0';
	cout << "Input a new int:\n";
	s_int.read_val(i);
	cout << "Input a new char:\n";
	s_char.read_val(c);
	cout << "Input a new double:\n";
	s_d.read_val(d);
	cout << "Input a new string:\n";
	s_str.read_val(s);
	cout << "New Values:\n" << s_int.get() << " " << s_char.get() << " " << s_d.get() << " " << s_str.get() << endl;*/
	cout << "Input as many ints as you like:\n";

	vector<int> we;
	s_v.read_val(we);
	cout << s_v.get();

	return 0;
}