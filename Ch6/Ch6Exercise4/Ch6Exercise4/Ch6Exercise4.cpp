#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void error(string s)
{
	throw runtime_error(s);
}

class Name_value
{
	string name = "";
	int value = 0;

public:
	Name_value(string inName, int inVal)
		:name(inName), value(inVal) {};

	string get_name() { return name; }

	int get_value() { return value; }
};

void Score()
{
	cout << "Enter the player name and score (Joe 42):\n";
	string name = "";
	int score = 0;
	vector<Name_value> scoreboard;
	vector<string> names;
	vector<int> scores;
	char check = 'n';

	while (check == 'n')
	{
		cin >> name >> score;
		if (name != "NoName")
		{
			bool goodName = true;
			if (scoreboard.size() > 0)
			{
				for (int i = 0; i < scoreboard.size(); ++i)
				{
					string testName = scoreboard[i].get_name();
					if (testName == name)
						goodName = false;
				}
			}

			if (goodName == true)
			{
				scoreboard.push_back(Name_value(name, score)); //creates object of name+score and adds to vector
			}
			else
				cout << "Error, name already exists.\n";
		}
		else
			check = 'y';
	}

	for (int i = 0; i < scoreboard.size(); ++i)
	{
		cout << scoreboard[i].get_name() << "\t" << scoreboard[i].get_value() << endl;
	}

	char breakLoop1 = 'n';
	do
	{
		cout << "Enter a name to find their score: ";
		string checkName = "";
		cin >> checkName;
		cin.ignore();
		bool result = false;
		for (int i = 0; i < scoreboard.size(); i++)
		{
			string testName = scoreboard[i].get_name();
			if (checkName == testName)
			{
				cout << checkName << "\t" << scoreboard[i].get_value() << endl;
				result = true;
			}
		}
		if (result == false)
			cout << "Error, name not found\n";

		cout << "Would you like to perform another search?(Y/N)\n";
		cin >> breakLoop1;
		breakLoop1 = tolower(breakLoop1);
		cin.ignore();
	} while (breakLoop1 == 'y');

	char breakLoop2 = 'n';
	do
	{
		cout << "Enter a score to find a player: ";
		int checkScore = 0;
		cin >> checkScore;
		cin.ignore();
		bool result = false;

		for (int i = 0; i < scoreboard.size(); ++i)
		{
			int testScore = scoreboard[i].get_value();
			if (checkScore == testScore)
			{
				cout << scoreboard[i].get_name() << " has score " << checkScore << endl;
				result = true;
			}
		}
		if (result == false)
			cout << "No player has that score.\n";

		cout << "Would you like to search another score?(Y/N)\n";
		cin >> breakLoop2;
		cin.ignore();
		breakLoop2 = tolower(breakLoop2);
	} while (breakLoop2 == 'y');
}

void Ch6Ex9()
{
	cout << "Enter an integer to breakdown: ";
	vector<char> numbers;
	string userNum = "";
	cin >> userNum;

	try {
		for (char c : userNum)
		{
			switch (c) {
			case'1':case '2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':case'0':
				numbers.push_back(c);
				break;
			default:
				error("Improper user input: Ensure to only input integers");
			}
		}

		vector<char>::iterator zero = numbers.begin();

		while (numbers[0] == '0')
		{

			numbers.erase(zero);
			zero = numbers.begin();
		}
		int caseCount = 0;
		string readOut = "";

		for (int i = numbers.size() - 1; i >= 0; --i)
		{
			string simple{ numbers[i] };
			switch (caseCount) {
			case 0:
				readOut = simple + " ones.";
				++caseCount;
				break;
			case 1:
				readOut = simple + " tens and " + readOut;
				++caseCount;
				break;
			case 2:
				readOut = simple + " hundreds and " + readOut;
				++caseCount;
				break;
			case 3:
				readOut = simple + " thousands and " + readOut;
				++caseCount;
				break;
			case 4:
				readOut = simple + " tens of thousands and " + readOut;
				++caseCount;
				break;
			}
		}

		if (readOut != "") cout << endl << readOut << endl;
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
}

int main()
{
	//Score();

	Ch6Ex9();

	return 0;
}