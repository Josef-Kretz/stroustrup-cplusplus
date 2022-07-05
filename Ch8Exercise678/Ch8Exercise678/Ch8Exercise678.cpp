#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

template<typename T>
void Print(const vector<T>& v)
{
	for (T i : v)
		cout << i << endl;
}

template<typename T, typename Y>
void Print(const vector<T>& vt, const vector<Y> vy)
{
	for (int i = 0; i < vt.size(); ++i)
	{
		cout << vt[i] << "\t" << vy[i] << endl;
	}
}




class Obit
{
	string name;
	double age;

public:
	Obit(string s, double d)
		:name(s), age(d) {}

	double get_age()
	{
		return age;
	}

	string get_name()
	{
		return name;
	}
};

double FindAge(string name, const vector<Obit>& userList)
{
	for (Obit person : userList)
	{
		if (name == person.get_name())
			return person.get_age();
	}

	return 0;
}

int main()
{
	vector<string> names;
	vector<double> ages;
	vector<Obit> userList;

	string tempName;
	double tempAge = 0;

	cout << "Enter names and ages of people you know:\n";
	
	while (cin >> tempName >> tempAge)
	{
		names.push_back(tempName);
		ages.push_back(tempAge);
		userList.push_back(Obit(tempName, tempAge));
	}

	Print(names, ages);

	sort(names.begin(), names.end());

	for (string name : names)
		cout << name << "\t" << FindAge(name, userList) << endl;

	return 0;
}