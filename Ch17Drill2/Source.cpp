#include <iostream>
#include <vector>

using namespace std;

void print_array(ostream& os, int* a, int n)
{
	for (int i = 0; i < n; ++i)
		os << a[i] << " ";
	os << endl;
}

int main()
{
	int x1 = 7;
	int* p1 = &x1;
	cout << p1 << ": " << *p1 << endl;

	int* p2 = new int[7]{ 1,2,4,8,16,32,64 };
	cout << p2 << ": ";
	print_array(cout, p2, 7);

	int* p3 = p2;
	p2 = p1;
	p2 = p3;

	cout << "p1 : " << p1 << " : ";
	print_array(cout, p1, 1);
	cout << "p2 : " << p2 << " : ";
	print_array(cout, p2, 7);

	delete[] p2, p3;

	p1 = new int[10]{ 1,2,4,8,16,32,64,128,256,512 };

	p2 = new int[10];

	for (int i = 0; i < 10; ++i)
		p2[i] = p1[i];
	
	cout << "p1: " << p1 << ": ";
	print_array(cout, p1, 10);

	cout << "p2: " << p2 << ": ";
	print_array(cout, p2, 10);

	delete[] p1, p2;

	vector<int> v1{ 1,2,4,8,16,32,64,128,256,512 };

	vector<int> v2 = v1;

	cout << "v1: ";
	for (int i : v1)
		cout << i << " ";
	cout << endl
		<< "v2: ";
	for (int i : v2)
		cout << i << " ";
	cout << endl;

	return 0;
}