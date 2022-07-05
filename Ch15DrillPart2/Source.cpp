#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Person
{
	Person() {}
	Person(string fn, string ln, int a) 
	{
		//check if age is between 0 and 150
		if (a < 0 || a > 150) throw runtime_error("Illegal age input");
		//check if non-alphabetic chars in name
		for (char c : fn)
			if (!isalpha(c)) throw runtime_error("Illegal characters in name input");
		for(char c : ln)
			if (!isalpha(c)) throw runtime_error("Illegal characters in name input");

		first_name = fn;
		last_name = ln;
		age = a;
	}

	string Name() { return first_name + " " + last_name; }
	int Age() { return age; }

private:
	string first_name, last_name;
	int age = -1;
};

istream& operator >> (istream& is, Person& p)
{
	string fname, lname;
	int age;

	if (is >> fname >> lname >> age)
	{
		p = Person(fname, lname, age);
		return is;
	}
	else
	{
		is.setstate(ios_base::failbit);
		return is;
	}
	
}


ostream& operator <<(ostream& os, Person p)
{
	return os << p.Name() << " " << p.Age() << endl;
}

void Input_People(vector<Person>& people)
{
	Person p;
	try {
		while (cin >> p)	//loop as long as user provides info
		{
			people.push_back(p);
		}
		cin.clear();	//if user stops or input error, reset bit flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
}

bool hasAlpha(const string& s)
{
	for (char c : s)
		if (isalpha(c)) return true;
	return false;
}

int main()
{
	vector<Person> people;

	try
	{
		char check = 'n';
		do
		{
			cout << "Enter a person's name and age:\n";
			Input_People(people);	//loops until user stop entering Person data
			

			cout << "Would you like to exit?(Y/N)\n";
			cin >> check;
			check = tolower(check);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (check != 'y');
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	
	for (Person p : people)
		cout << p;

	return 0;
}