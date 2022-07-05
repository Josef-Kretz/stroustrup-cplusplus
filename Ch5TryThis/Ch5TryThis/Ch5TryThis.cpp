#include <iostream>
#include <vector>

using namespace std;

void error(string s)
{
	cerr << s << endl;
}

int area(int length, int width)
{
	if (length <= 0 || width <= 0) error("area pre condition");
	int a = length * width;
	if (a <= 0)error("area() post condition");
	return a;
}

int framed_area(int x, int y)
{
	return area(x-2, y-2);
}

int f(int x, int y, int z)
{
	try
	{
		int area1 = area(x, y);
		if (area1 <= 0)error("non-positive area");
		int area2 = framed_area(12, z);
		if (area2 <= 0)error("non-positive area");
		int area3 = framed_area(y, z);
		if (area3 <= 0)error("non-positive area");
		double ratio = double(area1) / area3;

		cout << area1 << endl
			<< area2 << endl
			<< area3 << endl
			<< ratio << endl;
	}
	catch (runtime_error& e)
	{
		cerr << "runtime error: " << e.what() << '\n';
		return 1;
	}




	return 0;
}

int main()
{
	//int s1 = area(-7,2);
	//int s2 = area(7,-2);
	int s3 = area(-7,-2);
	/*int s4 = area(int{ '7' },2);

	int x0 = area(7,2);
	int x1 = area(7,2);
	int x2 = area(7, 2);*/

	//f(-22, 22, 3);

	
	/*int no_of_temps = 0;
	double sum = 0;
	double high_temp = -10000000;
	double low_temp = 100000;


	for (double temp; cin >> temp;) //read and put into temps
	{
		++no_of_temps;
		if (temp > high_temp)high_temp = temp; //find high
		if (temp < low_temp)low_temp = temp; //find low
		sum += temp; //compute sum
	}
	

	cout << "High temp: " << high_temp << endl
		<< "Low temp: " << low_temp << endl
		<< "Average temp: " << sum / no_of_temps << endl;*/

	return 0;
}