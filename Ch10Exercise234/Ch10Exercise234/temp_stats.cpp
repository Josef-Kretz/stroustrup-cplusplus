#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

double TempCtoF(double t)
{
	t *= 1.8;
	t += 32;
	return t;
}

struct Reading {
	int hour;
	double temperature;
	char unit;
};
bool operator<(const Reading& r1, const Reading& r2)
{
	return r1.temperature < r2.temperature;
}
istream& operator>>(istream& is, Reading& r)
{
	char lbracket, comma, unit, rbracket;
	int hour;
	double temperature;

	if (is >> lbracket && lbracket != '(') throw runtime_error("Input does not begin with '('\n");
	
	is >> hour >> comma >> temperature >> unit >> rbracket;
	if (!is) return is;
	if (comma != ',' || rbracket != ')') throw runtime_error("Bad data formatting\n");

	unit = tolower(unit);
	if (unit == 'c')
		temperature = TempCtoF(temperature);

	r.hour = hour;
	r.temperature = temperature;
	r.unit = unit;

	return is;
}

vector<Reading> IFVector()
{
	ifstream ifs{ "raw_temps.txt" };
	if (!ifs) throw runtime_error("Cannot open input file\n");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	vector<Reading> toReturn;

	for (Reading r; ifs >> r;)
		toReturn.push_back(r);

	if (toReturn.size() > 0) return toReturn;
	throw runtime_error("No data found\n");
}

double Median(vector<Reading> rVec)
{
	if (rVec.empty()) throw runtime_error("Passed empty vector to Median()\n");
	int size = rVec.size() / 2;
	double med;
	sort(rVec.begin(), rVec.end());

	if (rVec.size() > 2)
	{
		med = rVec[size - 1].temperature + rVec[size].temperature + rVec[size + 1].temperature;
		med /= 3;
		return med;
	}
	if (rVec.size() == 2)
	{
		med = rVec[size - 1].temperature + rVec[size].temperature;
		med /= 2;
		return med;
	}

	return rVec[0].temperature;
}

double Mean(vector<Reading> rVec)
{
	double mean, sum = 0;

	for (Reading r : rVec)
		sum += r.temperature;
	
	mean = sum / rVec.size();

	return mean;
}
int main()
{
	try {
		vector<Reading> temp = IFVector();
		
		for (Reading r : temp)
			cout << r.hour << " " << r.temperature << r.unit << endl;

		cout << "Median temperature: " << Median(temp) << 'f' << endl
			<< "Mean temperature: " << Mean(temp) << 'f' << endl;

		cout << "Test conversion: " << TempCtoF(100);
	}
	catch (runtime_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	return 0;
}