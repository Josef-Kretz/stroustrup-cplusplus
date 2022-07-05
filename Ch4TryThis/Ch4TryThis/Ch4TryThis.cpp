#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void MoneyChanger1()
{
	char unit = ' ';
	double money = 0.0;
	char answer = 'n';
	do {
		cout << "Please enter an amount of money, followed by its denomination char ('y', 'k', 'p'):\n";
		cin >> money >> unit;

		switch (unit)
		{
		case 'y':
			money *= 0.0119;
			cout << "$" << money << " CAD" << endl;
			break;
		case 'p':
			money *= 1.7737;
			cout << "$" << money << " CAD" << endl;
			break;
		case 'k':
			money *= 0.20615;
			cout << "$" << money << " CAD" << endl;
			break;
		default:
			cout << "Improper unit detected.\n";
			break;
		}

		cout << "Would you like to do another conversion?(Y/N)\n";
		cin >> answer;
		cin.ignore();
		answer = toupper(answer);
	} while (answer == 'Y');
}

void CharLooper2()
{
	for (char letter = '0'; letter != 'Z' + 1; ++letter)
	{
		cout << letter << "\t" << int(letter) << endl;
	}
}


void Dictionary()
{
	vector<string> bleeps{ "sugar","pop","soda","candy" };
	
	string testWords = "";
	while (cin >> testWords)
	{
		vector<string>::const_iterator wordBlock = find(bleeps.cbegin(), bleeps.cend(), testWords);
		if (wordBlock != bleeps.cend())
			cout << "BLEEP\n";
		else if (wordBlock == bleeps.cend())
			cout << testWords << endl;
		else
			cout << "Error: Consult nearest programmer.";
	}
}


int SelfMultiplier(int num)
{
	int total =0;
	for (int count = 0; count < num; ++count)
	{
		total += num;
	}
	return total;
}

int main()
{
	MoneyChanger1();
	CharLooper2();

	for (int count = 0; count < 100; ++count)
	{
		cout << count << "\t" << SelfMultiplier(count) << endl;
	}

	Dictionary();

	return 0;
}