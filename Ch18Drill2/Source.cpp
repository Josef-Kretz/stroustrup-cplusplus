#include <iostream>
#include <vector>

std::vector<int> gv{ 1,2,4,8,16,32,64,128,256,512 };

void f(std::vector<int> v)
{
	std::vector<int> lv(v.size());
	for (int i = 0; i < v.size(); ++i)
		lv[i] = v[i];
	for (int i : lv)
		std::cout << i << " ";
	std::cout << std::endl;

	std::vector<int>lv2 = lv;

	for (int i : lv2)
		std::cout << i << " ";
	std::cout << std::endl;
}

int factorial(int n)
{
	return (n > 1) ? (n * factorial(n - 1)) : 1;
}

int main()
{
	f(gv);

	std::vector<int> vv;
	for (int i = 0; i < 10; ++i)
		vv.push_back(factorial(i + 1));
	f(vv);
}