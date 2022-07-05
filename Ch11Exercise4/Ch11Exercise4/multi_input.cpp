#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	cout << "Input any number of integers in dec, oct, or hex:\n";
	vector<string> numsString;
	string userNum;
	while (cin >> userNum)
	{
		if (!isdigit(userNum[0]) && userNum[0] != '-')
		{
			cout << "Error not an integer\n";
		}
		else
			numsString.push_back(userNum);
	}

	for (string s : numsString)
	{
		istringstream iss{ s };
		if (s.size() > 1)
		{
			if (s[0] == '0')
			{
				if (s[1] == 'x')
				{
					int ii;
					iss >> hex >> ii;
					cout << s << "\t hex converts to \t"  << ii << endl;
				}
				else
				{
					int ii;
					iss.unsetf(ios::dec);
					iss >> oct >> ii;
					cout << s << "\t oct converts to \t" << ii << endl;
				}
			}
		}
		
		if (s[0] != '0' )
		{
			int ii;
			iss >> ii;
			cout << s << "\t dec converts to \t" << ii << endl;
		}
	}

	return 0;
}