//chapter 25 drill

#include <iostream>
#include <bitset>

using namespace std;

template<typename T> void print(T i)
{
	cout << dec << i << "=="
		<< hex << "0x" << i << "=="
		<< bitset<8 * sizeof(T)>(i) << endl;
}

int main()
{
	unsigned int v = 1;
	for(int i = 0;i<sizeof(v)*8;++i)
	{
		cout << v << ' ';
	}
	cout << endl;

	cout << "Define short unsigned ints using hexadecimal literals:\n";
	short unsigned int i1 = 0xffff;
	print(i1);

	i1 = 0x1;
	print(i1);

	i1 = 0x8000;
	print(i1);

	i1 = 0x000f;
	print(i1);

	i1 = 0xf000;
	print(i1);

	i1 = 0x5555;
	print(i1);

	i1 = 0xaaaa;
	print(i1);

	cout << "Redo above drill, using bit operations and literals 1 and 0:\n";
	i1 = 1;
	for (int i = 0; i < (sizeof(i1) * 8)-1; ++i)
		i1 = (i1 | (i1 << 1));
	print(i1);

	i1 = 1;
	print(i1);

	i1 = i1 << 15;
	print(i1);

	i1 = i1 >> 15;
	for (int i = 0; i < 3; ++i)
		i1 = (i1 | (i1 << 1));
	print(i1);

	i1 = i1 << 12;
	print(i1);

	i1 = 1;
	for (int i = 0; i < 7; ++i)
		i1 = (i1 | (i1 << 2));
	print(i1);

	i1 = 1;
	i1 = i1 << 1;
	for (int i = 0; i < 7; ++i)
		i1 = (i1 | (i1 << 2));
	print(i1);
}