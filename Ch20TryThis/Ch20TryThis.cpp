// Ch20TryThis.cpp : Try This exercises found within chapter 20
#include <iostream>
#include<vector>
#include <list>
#include <string>

using namespace std;

double* get_from_jack(int* count)
//jack puts doubles into an array
//returns number of elements with *count
{
	double* jack = new double[5]{ 1,2,3,4,5 };
	*count = 5;
	return jack;
}

vector<double>* get_from_jill()
{
	return new vector<double>{ 6,7,8,9,10 };
}

double* high1(double* first, double* last)
{
	double h = -1;
	double* high = nullptr;
	for (double* p = first; p != last; ++p)
	{
		if (h < *p) { high = p; h = *p; }
	}
	return high;
}

void copy1(int* f1, int* e1, int* f2)
{
	if (f2 != nullptr) delete[] f2;
	f2 = new int[e1 - f1];

	while (f1 != e1)
	{
		*f2 = *f1;
		++f1;
		++f2;
	}
}

template<typename Iterator>
Iterator high2(Iterator first, Iterator last)
{
	if (first == last || first == nullptr)  return first; 
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*high < *p) high = p;
	return high;
}

template<typename Iter>
void advance(Iter& p, int n)//requires forward iterator Iter
{
	while (0 < n) { ++p; --n; }
	while (0 > n) { --p; ++n; }
}

template<typename Iter1, typename Iter2>
bool check_hello(Iter1 f1, Iter1 e1, Iter2 f2, Iter2 e2)
{
	unsigned int size1 = 0;
	unsigned int size2 = 0;

	for (auto p = f1; p != e1; ++p) ++size1;
	for (auto p = f2; p != e2; ++p) ++size2;

	if (size1 != size2) return false;

	while (f1 != e1)
	{
		if (*f1 != *f2) return false;
		++f1; ++f2;
	}
	return true;
}

void fct1()
{
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);

	vector<double>* jill_data = get_from_jill();

	double h = -1;
	double* jack_high = nullptr;	//jack high will point to element with highest value
	double* jill_high = nullptr;	//jill high will point to element with highest value

	for (int i = 0; i < jack_count; ++i)
	{
		if (h < jack_data[i]) {
			jack_high = &jack_data[i];	//save address of largest element
			h = jack_data[i];	//update "largest element"
		}
	}

	h = -1;
	vector<double> &jdat = *jill_data;
	for (unsigned int i = 0; i < jill_data->size(); ++i)
	{
		if (h < jdat[i])
		{
			jill_high = &jdat[i];	//save address of largest element
			h = jdat[i];			//update "largest element"
		}
	}

	if (jill_high != nullptr && jack_high != nullptr)
		cout << "Jill's max " << *jill_high
		<< "; Jack's max " << *jack_high << endl;

	delete[] jack_data;
	delete jill_data;
}

void fct2()
{
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);

	vector<double>* jill_data = get_from_jill();
	vector<double>& jdat = *jill_data;

	double h = -1;
	double* jack_high = high1(jack_data, jack_data + jack_count);	//jack high will point to element with highest value
	double* jill_high = high1(&jdat[0], &jdat[0] + jdat.size());	//jill high will point to element with highest value

	cout << "Jill's highest data point: " << *jill_high << endl
		<< "Jack's highest data point: " << *jack_high << endl;
}

void fct3()
{
	int* ia1 = new int[5]{ 1,2,3,4,5 };
	int* ia2 = new int[5]{ 5,6 };

	cout << "Initial value of ia2: "
		<< ia2[0] << " " << ia2[1] << endl;

	copy1(ia1, ia1 + 5, ia2);

	cout << "New value of ia2: ";
	for (int* i = ia2;i != ia2+5;++i)
		cout << *i << " ";
	cout << endl;
}

void fct4()
{
	int jack_count = 0;

	double* jack_data = get_from_jack(&jack_count);
	vector<char>* jill_data = new vector<char>{ 'a','b','c','d','e' };
	vector<char>& jdat = *jill_data;

	double* jack_high = high2(jack_data, jack_data + jack_count);
	char* jill_high = high2(&jdat[0], &jdat[0] + jdat.size());

	if (jack_high != nullptr || jill_high != nullptr)
		cout << "Jill's high: " << *jill_high
		<< "; Jack's high: " << *jack_high << endl;

	delete[] jack_data;
	delete jill_data;
}

void fct5()
{
	char* ca1 = new char[5]{ 'h','e','l', 'l', 'o' };
	cout << "Values stored in ca1: ";
	for (char* c = ca1; c != ca1 + 5; ++c)
		cout << *c << " ";
	cout << endl;

	char* c_pos = ca1;
	advance(c_pos, 4);
	cout << "c_pos points to value: " << *c_pos << endl;
	advance(c_pos, -3);
	cout << "c_pos now points to value: " << *c_pos << endl;
}

void fct6()
{
	vector<char> vc{ 'H','e','l','l','o' };
	list<char> lc{ 'H','e','l','l','o' };
	char c[]{ 'H','e','l','l','o' };
	string s = "Hello";

	
}

void fct7()
{

}

int main()
{

	fct1();
	fct2();
	fct3();
	fct4();
	fct5();
	fct6();
	fct7();
}
