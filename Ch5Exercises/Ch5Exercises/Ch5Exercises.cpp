#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

void error(string s)
{
	throw runtime_error(s);
}

double CToK(double c) //converts celsius to kelvin
{
	try
	{
		if (c <= -273.15)error("Temperature too low");
		double k = c + 273.15;
		return k;
	}
	catch (runtime_error& e)
	{
		//cerr << "Error: " << e.what() << endl;
		throw e;
	}
}

double KToC(double k)
{
	try
	{
		if (k < 0)error("Temperature too low");
		double c = k - 273.15;
		return c;
	}
	catch (runtime_error& e)
	{
		//cerr << "Error: " << e.what() << endl;
		throw e;
	}
}

void KelvinConverter()
{
	try {
		cout << "Enter a celsius value to convert to kelvin: ";
		double c = 0.0;

		cin >> c;
		double k = CToK(c); //convert temperature
		cout << endl << k << endl; //output kelvins

		cout << "Enter a kelvin value to convert to celsius: ";
		cin >> k;
		c = KToC(k);
		cout << endl << c << endl;
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "Unknown error" << endl;
	}
	
}

double CToF(double c)
{
	double f = 9.0 / 5 * c + 32;
	return f;
}

double FToC(double f)
{
	double c = (f - 32) * (5.0 / 9);
	return c;
}

void CelsiusFahrenheit()
{
		double temp = 0.0;
		double result = 0.0;
		char unit = '\0';
		cout << "Enter a temperature follow by C or F: ";
		cin >> temp >> unit;
		unit = toupper(unit);
		if (unit == 'C')
			result = CToF(temp);
		else if (unit == 'F')
			result = FToC(temp);
		else
			cerr << "Incorrect input" << endl;
		if (unit == 'C')
			cout << temp << unit << "->" << result << 'F' << endl;
		else if (unit == 'F')
			cout << temp << unit << "->" << result << 'C' << endl;
		else
			cerr << "Unknown error" << endl;
}


void QuadFinder(double a, double b, double c)
{
	try
	{
		double zeroCheck = (b * b) - (4 * a * c);
		if (zeroCheck < 0)error("No real roots passed to QuadFinder");

		double x1 = (0 - b) + sqrt(zeroCheck);
		x1 /= (2 * a);

		double x2 = (0 - b) - sqrt(zeroCheck);
		x2 /= (2 * a);

		cout << "Positive root: " << x1
			<< endl << "Negative root: " << x2 << endl;
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
}

void NVector()
{
	try
	{
		vector<double> userNums;
		double temp = 0;
		int nSum = 0;
		double sum = 0;
		string numList = "";

		cout << "Enter the number of values you want to sum: ";
		cin >> nSum;
		cin.ignore();
		if (nSum <= 0)error("Invalid value supplied");

		cout << "Enter a number of integers (Enter '|' to stop):\n";
		while (cin >> temp)
		{
			if(cin)
				userNums.push_back(temp);
		}

		if (nSum > userNums.size())error("Not enough values submitted");

		for (int i = nSum - 1; i >= 0; --i)
		{
			sum += userNums[i];
			numList = to_string(userNums[i]) + " " + numList;
		}

		cout << "The sum of the first " << nSum << " numbers ( " << numList << ") is " << sum << endl;
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
}

void Fibonacci()
{
	int first = 0;
	int second = 1;
	int sum = 0;
	int check = 0;

	while (check <= 44) //44th number in fibonacci sequence is under max limit of int, 45th is over limit
	{
		++check;
		sum = first + second;
		first = second;
		second = sum;
		cout << sum << endl;
	}
}

int main()
{
	//KelvinConverter();
	//CelsiusFahrenheit();
	//QuadFinder(-200,92000,8400000);
	//NVector();
	Fibonacci();

	return 0;
}