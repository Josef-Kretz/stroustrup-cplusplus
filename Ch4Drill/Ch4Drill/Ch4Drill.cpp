#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	double first = 0.0;
	string unit = "";

	vector<double> userNums;

	while (cin >> first >> unit)
	{
		cout << first << unit << endl;
		if (unit == "m")
		{
			userNums.push_back(first);
		}
		else if (unit == "cm")
		{
			first /= 100;
			userNums.push_back(first);
		}

		else if (unit == "in")
		{
			first *= 0.0254;
			userNums.push_back(first);
		}

		else if (unit == "ft")
		{
			first *= 0.3048;
			userNums.push_back(first);
		}
		else
			cout << "Illegal unit: please only use cm, in, ft, m\n";

		sort(userNums.begin(), userNums.end());
		double sum = 0;
		for (double count : userNums)
		{
			sum += count;
		}

		cout << userNums.size() << " number(s) have been entered.\n";
		cout << "Total of entered numbers: " << sum << endl;
		cout << "Smallest entered number: " << userNums[0] << endl;
		cout << "Largest entered number: " << userNums[userNums.size() - 1] << endl;
	}

	cout << "User input suspended, displaying legally entered numbers:\n";
	for (double num : userNums)
		cout << num << ' ';
	cout << endl;
	return 0;
}