#include <iostream>
#include <vector>

using namespace std;

void print_array10(ostream& os, int* a)
{
	for (int i = 0; i < 10; ++i)
		os << a[i] << " ";
	os << endl;
}

void print_array(ostream& os, int* a, int n)
{
	for (int i = 0; i < n; ++i)
		os << a[i] << " ";
	os << endl;
}

void print_vector(ostream& os, vector<int> v)
{
	for (int i : v)
		os << i << " ";
	os << endl;
}

int main()
{
	cout << "Drill 1: Number 1 to 3\n";
	int* int_array = new int[10]{ 0,1,2,3,4,5,6,7,8,9 };
	for (int i = 0; i < 10; ++i)
	{
		cout << int_array[i] << endl;
	}
	delete[] int_array;

	cout << "Drill 1: Number 4 to 5\n";
	int* ten_ints = new int[10]{ 100, 101, 102, 103, 104, 105, 106, 107, 108, 109 };
	print_array10(cout, ten_ints);
	delete[] ten_ints;

	cout << "Drill 1: Number 6 to 7\n";
	int* eleven_ints = new int[11]{ 100,101,102,103,104,105,106,107,108,109,110 };
	print_array(cout, eleven_ints, 11);
	delete[] eleven_ints;

	cout << "Drill 1: Number 8\n";
	int* twenty_ints = new int[20];
	for (int i = 0; i < 20; ++i)
	{
		twenty_ints[i] = i + 100;
	}

	print_array(cout, twenty_ints, 20);
	delete[] twenty_ints;

	cout << "Drill 1: Number 10\n";
	vector<int> v1, v2, v3;

	//generate values 100-109 in each vector
	for (int i = 0; i < 10; ++i)
	{
		v1.push_back(i + 100);
		v2.push_back(i + 100);
		v3.push_back(i + 100);
	}
	//generate additional values 110-119 in v3
	for (int i = 0; i < 10; ++i)
		v3.push_back(i + 110);

	print_vector(cout, v1);
	print_vector(cout, v2);
	print_vector(cout, v3);


	return 0;
}