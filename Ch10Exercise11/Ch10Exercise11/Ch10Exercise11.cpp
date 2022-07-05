#include <iostream>
#include <fstream>

using namespace std;

int IntFinder(ifstream& ifs)
{
	int num;
	ifs >> num;
	if (ifs.eof() && !ifs.fail()) return num;

	if (ifs.fail())
	{
		ifs.clear();
		char c;
		ifs >> c;
	}

	if(ifs.good()) return num;
	return 0;
}

int main()
{
	string starterFile = "first.txt";

	ifstream ifs{ starterFile };
	if (!ifs) throw runtime_error(starterFile + " not found\n");

	int sum = 0;

	while (ifs.good())
	{
		sum += IntFinder(ifs);
	}

	cout << "Final sum: " << sum;

	return 0;
}