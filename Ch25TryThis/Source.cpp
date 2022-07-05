//chapter 25 try this exercises

#include <iostream>
#include <bitset>

using namespace std;

void tryBits()
//try out binary and hexadecimal notations
{
	for (unsigned i; cin >> i;)
		cout << dec << i << "=="
		<< hex << "0x" << i << "=="
		<< bitset<8 * sizeof(unsigned)>{i} << endl;
}

void infinite()
//the difference between unsigned and signed char
//results in an infinite loop
{
	unsigned char max = 160; //very large
		for (signed char i = 0; i < max; ++i) //signed char overflows before reaching unsigned char max
			cout << int(i) << endl;
}

template<typename T> void print(T i)
{
	cout << int(i) << '\t' << bitset<8 * sizeof(T)>(i) << endl;
}

void implicit_conversion()
{
	int si = 257;
	char c = si;
	unsigned char uc = si;
	signed char sc = si;

	print(si); print(c); print(uc); print(sc); cout << endl;

	si = 128;
	c = si;
	uc = si;
	sc = si;
	print(si); print(c); print(uc); print(sc); cout << endl;
}

int main()
{
	//tryBits();

	//infinite();

	implicit_conversion();

	return 0;
}