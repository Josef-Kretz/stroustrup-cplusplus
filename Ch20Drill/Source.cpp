#include <iostream>
#include <vector>
#include <list>
#include <array>

using namespace std;

template<typename Iter1, typename Iter2>
//requires input_iterator<Iter1>() && Output_iterator<Iter2>()
Iter2 copy1(Iter1 f1, Iter1 e1, Iter2 f2)
{
	if (f1 == e1) return f2;

	while (f1 != e1)
	{
		*f2 = *f1;
		++f1;
		++f2;
	}

	return f2;
}

template<typename Iter1>
void sumup(Iter1 f1, Iter1 e1, int i)
{
	while (f1 != e1)
	{
		*f1 += i;
		++f1;
	}
}

template<typename Iter1, typename Iter2>
int indexer(Iter1 f1, Iter1 e1, Iter2 f2)
{
	int count = 0;

	while (f1 != e1)
	{
		if (*f1 == *f2) return count;
		++count;
		++f1;
	}

	return -1;
}

int main()
{
	array<int, 10> tenA { 0,1,2,3,4,5,6,7,8,9 };
	vector<int> tenV{ 0,1,2,3,4,5,6,7,8,9 };
	list<int> tenL{ 0,1,2,3,4,5,6,7,8,9 };

	array<int, tenA.size()> ctenA = tenA;
	vector<int> ctenV = tenV;
	list<int> ctenL = tenL;
	
	sumup(ctenA.begin(), ctenA.end(), 2);
	sumup(ctenV.begin(), ctenV.end(), 3);
	sumup(ctenL.begin(), ctenL.end(), 5);

	copy1(ctenA.begin(), ctenA.end(), tenV.begin());
	copy1(ctenL.begin(), ctenL.end(), tenA.begin());

	cout << "Copied into vector: ";
	for (int i : tenV)
		cout << i << ' ';
	cout << endl;

	cout << "Copied into array: ";
	for (int i : tenA)
		cout << i << " ";
	cout << endl;

	vector<int>::iterator find3 = find(tenV.begin(), tenV.end(), 3);
	list<int>::iterator find27 = find(ctenL.begin(), ctenL.end(), 27);


	if (find3 != tenV.end())
	{
		int find3Index = indexer(tenV.begin(), tenV.end(), find3);
		cout << "Value " << *find3 << " found in position " << find3Index << endl;
	}

	if (find27 != ctenL.end())
	{
		int find27Index = indexer(ctenL.begin(), ctenL.end(), find27);
		cout << "Value " << *find27 << " found in position " << find27Index << endl;
	}

	return 0;
}