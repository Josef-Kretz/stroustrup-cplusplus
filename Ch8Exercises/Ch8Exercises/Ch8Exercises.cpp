#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Print(string s, vector<int> vec)
{
	cout << s << endl;
	for (int i : vec) { cout << i << endl; }
}

void Fibonacci(int x, int y, vector<int>& v, int n)
{
	if (!(v.empty())) throw runtime_error("Error");

	v.push_back(x);
	v.push_back(y);

	while (v.size() < n)
	{
		int temp = y;
		y += x;
		x = temp;
		v.push_back(y);
	}

	return;
}

vector<int> FReverse(const vector<int>& v)
{
	vector<int> reversed;
	for (int i = v.size()-1; i >= 0; --i)
	{
		reversed.push_back(v[i]);
	}

	return reversed;
}

void ComplexReverse(vector<int>& v)
{
	
	for (int i = 0; i < v.size()/2; ++i)
	{
		swap(v[i], v[v.size()-1 - i]);
	}
}

int main()
{
	vector<int> num;
	Fibonacci(1, 1, num, 8);
	Print("Fibonacci: ", num);

	vector<int> rNum = FReverse(num);
	Print("Reversed Fibonacci: ", rNum);

	ComplexReverse(rNum);
	Print("Swapped Reversed Fibonacci: ", rNum);

	return 0;
}