#include <iostream>
#include <string>

using namespace std;

void RepeatedWords()
{
	int numOfWords = 0;
	string previous = " ";
	string current;
	while (cin >> current)
	{
		++numOfWords;
		if (previous == current)
			cout << "Repeated word: " << current << ", at word number: " << numOfWords << endl;
		previous = current;
	}
}

void Goodbye()
{
	string s = "Goodbye, cruel world!";
	cout << s << '\n';
}

void unsafeConversions()
{
	double d = 0;
	while (cin >> d)//loops aslong as numbers are typed
	{
		int i = d; //squeezes a double into an int
		char c = i; //squeezes an int into a char
		int i2 = c; //gets integer value of a char
		cout << "d == " << d << " i == " << i << " i2 == " << i2 << " char(" << c << ")\n";
	}
}

int main()
{
	//RepeatedWords();
	//Goodbye();
	unsafeConversions();

	return 0;
}