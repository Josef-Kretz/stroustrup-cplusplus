#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Reading {
	int hour;
	double temperature;
	char unit;

	Reading() {}
	Reading(int h, double t) : hour(h), temperature(t) {}
};

void OFStore(vector<Reading> rVec)
{
	ofstream ofs{ "raw_temps.txt" };
	if (!ofs) throw runtime_error("Can't open output file\n");

	for (Reading r : rVec)
		ofs << '(' << r.hour << ',' << r.temperature << ')' << endl;
}

void GetTemp()
{
	vector<Reading> temp;
	int hour;
	double temperature;
	cout << "Please input temperature readings by hour [space] temperature:\n";
	while (cin >> hour >> temperature)
	{
		if (hour < 0 || hour > 23) throw runtime_error("Invalid hour input\n");
		temp.push_back(Reading(hour, temperature));
	}

	if (temp.size() > 0) OFStore(temp);
}

/*int main()
{
	try {
		GetTemp();
	}
	catch (runtime_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	return 0;
}*/