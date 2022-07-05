#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Name_pairs
{
private:
	vector<string> name;
	vector<double> age;

public:
	Name_pairs() {}

	void read_names();
	void read_ages();
	void sort();

	bool pairCheck();
	vector<string> getName() const;
	vector<double> getAge() const;
};

bool Name_pairs::pairCheck()
{
	if (name.size() != age.size()) return false;
	if (name.size() == 0) return false;
	return true;
}

vector<string> Name_pairs::getName() const
{
	return name;
}

vector<double> Name_pairs::getAge() const
{
	return age;
}

void Name_pairs::read_names()
{
	cout << "Enter names you wish to store:\nEnter break to finish\n";
	string userString;
	while (cin)
	{
		getline(cin, userString);
		if (userString == "break") break;
		if(isalpha(userString[0]))
			name.push_back(userString); 
		else
			cerr<<"Improper name. Names begin with a letter\n";
	}
	read_ages();
}

void Name_pairs::read_ages()
{
	cout << "Enter the proper age for each name you provided:\n";
	for (string s : name)
	{
		int userNum = 0;
		cout << s << ": ";
		cin >> userNum;
		age.push_back(userNum);
	}

	if (name.size() != age.size()) throw runtime_error("Age not properly paired with name\n");

}

ostream& operator << (ostream & os, Name_pairs pair)
{
	if (!(pair.pairCheck())) throw runtime_error("Pair check failed\n");
	const vector<string> tempName = pair.getName();
	const vector<double> tempAge = pair.getAge();
	for (int i = 0; i < tempName.size(); ++i)
	{
		os << tempName[i] << ": " << tempAge[i] << endl;
	}
}

bool operator == (const Name_pairs first, const Name_pairs second)
{
	vector<string> firstNames = first.getName();
	vector<double> firstAges = first.getAge();

	vector<string> secondNames = second.getName();
	vector<double> secondAges = second.getAge();

	if (firstNames.size() != secondNames.size()) return false;
	int sizeCheck = firstNames.size() + firstAges.size() + secondNames.size() + secondAges.size();
	if ((sizeCheck / 4) != firstNames.size()) return false;

	for (int i = 0; i < firstNames.size(); ++i)
	{
		if (firstNames[i] != secondNames[i]) return false;
		if (firstAges[i] != secondAges[i]) return false;
	}

	return true;
}

bool operator != (const Name_pairs first, const Name_pairs second)
{
	return !(first == second);
}

void Name_pairs::sort()
{
	if (name.size() != age.size() || name.size() <= 0) throw runtime_error("Cannot sort invalid name, age pairings\n");
	vector<string> tempName = name;
	vector<double> tempAge(name.size());

	std::sort(name.begin(), name.end());

	for (int count = 0;count < name.size();++count) //loop through each element of sorted vector
	{
		for (int i =0;i<tempName.size();++i) //for each element in sorted vector, find in unsorted vector
		{
			if (tempName[i] == name[count]) //when match found
				tempAge[count] = age[i];	//store age pair at same index as sorted vector
		}
	}

	age = tempAge;
}

int main()
{
	Name_pairs userInfo;

	userInfo.read_names();

	Name_pairs copy = userInfo;
	//userInfo.sort();

	if (copy == userInfo) cout << "Well, they're the same\n";

	userInfo.sort();

	if (copy != userInfo) cout << "Well, they're not the same!\n";

	return 0;

}