//chapter 24, Try This exercises

#include <iostream>
#include <limits>

using namespace std;


void f(int i, double fpd)
{
	char c = i;		//yes:chars really are very small integers
	short s = i;	//beware an int may not fit in a short int
	i = i + 1;		//what if i was the largest int?
	long lg = i * i;	//beware a lon may not be any larger than an int
	float fps = fpd;	//beware a large double may not fit in a float
	i = fpd;		//truncates: eg 5.7 -> 5
	fps = i;		//you can lose precision (for very large int values)
	cout << "char c: " << c << "\nshort s: " << s << "\ni = " << i << "\nlong lg: " << lg
		<< "\nfloat fps: " << fps << "\ni = " << i << "\nfps: " << fps << endl;
}

void g()
{
	char ch = 0;
	for (int i = 0; i < 500; ++i)
		cout << int(ch++) << '\t';
}

int main()
{
	f(numeric_limits<int>::max(), numeric_limits<double>::max()); //pass any int or double, i chose max values
	g();

	return 0;
}