#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void TempsEx2()
{
	vector<double> temps;
	cout << "Input temperatures to store:\n";
	for (double userTemp; cin >> userTemp;)
		temps.push_back(userTemp);

	double mean = 0;
	for (double element : temps) mean += element;
	cout << "Average temperature is " << mean / temps.size() << " degrees Celsius\n";

	sort(temps.begin(), temps.end());
	double median = 0;
	median = temps[temps.size() / 2] + temps[(temps.size() / 2) - 1];
	median /= 2;
	cout << "Median temperature is " << median << " degrees Celsius\n";
}

void CityDistance3()
{
	cout << "Input distances between cities in kilometers:\n";
	vector<double> cityRange;
	for (double distance; cin >> distance;)
		cityRange.push_back(distance);

	double totalDistance = 0;
	for (double element : cityRange) totalDistance += element;

	cout << "Sum of all distances between cities: " << totalDistance << endl;
	cout << "Average distance between all cities: " << totalDistance / cityRange.size() << endl;
	sort(cityRange.begin(), cityRange.end());
	cout << "Shortest range between cities: " << cityRange[0] << " km\n";
	cout << "Greatest distance between cities: " << cityRange[cityRange.size() - 1] << "km\n";
}


void SimpleCalculator()
{
	double num1, num2;
	char op;
	char answer = 'n';
	do {
		cout << "Enter two numbers separated by an operator. Example:\n"
			<< "number (+, -, *, /) another_number\n";
		cin >> num1 >> op >> num2;
		switch (op)
		{
		case '+':
			cout << num1 + num2;
			break;
		case '-':
			cout << num1 - num2;
			break;
		case '*':
			cout << num1 * num2;
			break;
		case '/':
			cout << num1 / num2;
			break;
		default:
			cout << "Error: improper input.";
		}
		cout << endl;
		cout << "Would you like to perform another calculation?(Y/N)\n";
		cin >> answer;
		cin.ignore();
		answer = tolower(answer);
	} while (answer == 'y');
	
}

bool Multiple(int num)
{
	for (int i = 2; i < num; ++i)
	{
		if (num % i == 0)
			return false;
	}

	return true;
}

void PrimeNumGen()
{
	vector<int> primes;
	int max = 0;
	cout << "Enter an upper limit to search for prime numbers: ";
	cin >> max;
	cin.ignore();
	cout << endl;

	for (int count = 2; count < max; ++count)
	{
		if (Multiple(count))
			primes.push_back(count);
	}

	cout << "Prime numbers found: \n";
	for (int x : primes) cout << x << " ";
	cout << endl;
}


void Mode()
{
	vector<int> mode;
	int input = 0;
	int numMode = 0;
	int numStore = 0;
	int tempMode = 0;
	while (cin >> input)
		mode.push_back(input);

	sort(mode.begin(), mode.end());

	for (int i = 0; i < mode.size()-1; ++i)
	{
		if (mode[i] == mode[i + 1])
			++tempMode;
		else
			tempMode = 0;
		if (tempMode > numMode)
		{
			numMode = tempMode;
			numStore = mode[i];
		}
	}

	cout << numStore << " repeated " << numMode << " times\n";

}

void QuadForm(double a, double b, double c)
{
	double x1 = 0;
	double x2 = 0;

	x1 = (0 - b) + sqrt((b * b) - (4 * a * c));
	x1 /= (2 * a);

	x2 = (0 - b) - sqrt((b * b) - (4 * a * c));
	x2 /= (2 * a);

	cout << x1 << endl;
	cout << x2 << endl;
}

void Score()
{
	cout << "Enter the player name and score (Joe 42):\n";
	string name = "";
	int score = 0;
	vector<string> names;
	vector<int> scores;
	char check = 'n';

	while (check == 'n' )
	{
		cin >> name >> score;
		if (name != "NoName")
		{
			bool goodName = true;
			if (names.size() > 0)
			{
				for (int i = 0; i < names.size(); ++i)
				{
					if (names[i] == name)
						goodName = false;
				}
			}
			
			if (goodName == true)
			{
				names.push_back(name);
				scores.push_back(score);
			}
			else
				cout << "Error, name already exists.\n";
		}
		else
			check = 'y';
	}

	for (int i = 0; i < names.size(); ++i)
	{
		cout << names[i] << "\t" << scores[i] << endl;
	}

	char breakLoop1 = 'n';
	do
	{
		cout << "Enter a name to find their score: ";
		string checkName = "";
		cin >> checkName;
		cin.ignore();
		bool result = false;
		for (int i = 0; i < names.size(); i++)
		{
			if (checkName == names[i])
			{
				cout << checkName << "\t" << scores[i] << endl;
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

		for (int i = 0; i < scores.size(); ++i)
		{
			if (checkScore == scores[i])
			{
				cout << names[i] << " has score " << checkScore << endl;
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


int main()
{
	//TempsEx2();
	//CityDistance3();
	//SimpleCalculator();
	//PrimeNumGen();
	Mode();
	//QuadForm(3, -5, -8); //correct output of 2.66667 and -1


	//Score();

	return 0;
}