#include <iostream>


void f(int* ia, int n)
{
	int la[10];
	for (int i = 0; i < 10; ++i)
		la[i] = ia[i];
	for (int i = 0; i < 10; ++i)
		std::cout << la[i] << " ";
	std::cout << std::endl;

	int* p = new int[n];
	for (int i = 0; i < n;++i)
		p[i] = ia[i];
	for (int i = 0; i < n; ++i)
	{
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	delete[] p;
}

int ga[10]{ 1,2,4,8,16,32,64,128,256,512 };

int factorial(int n)
{
	return (n > 1) ? (n * factorial(n - 1)) : 1;
}

int main()
{
	try {
		f(ga, 10);

		int aa[10];
		for (int i = 1; i < 11; ++i)
			aa[i-1] = factorial(i);

		f(aa, 10);
	}
	catch (std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Error\n";
	}
	return 0;
}