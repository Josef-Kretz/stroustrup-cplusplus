//chapter 24, exercise 1

#include <iostream>

#include "Matrix.h"

int triple(int& i1)
{
	return i1 *= 3;
}

struct Triple1 {
	int operator()(int& i)
	{
		return i *= 3;
	}
};

template<typename T>
void triple2(T& t)
{
	t *= 3;
}

template<typename T>
T triple3(const T& t)
{
	return t * 3;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Numeric_lib::Matrix<T> m)
{
	int size = m.size();

	for (int i = 0; i < size; ++i)
		os << m(i) << ' ';
	return os;
}

int main()
{
	using namespace Numeric_lib;

	int aa1[]{ 1,2,3,4,5 };
	Matrix<int> a1 = aa1;

	//exercise 1
	//create function triple and apply() to matrix 2 ways
	std::cout << "Initial values:\n" << a1 << std::endl;

	std::cout << "copy of modified matrix:\n" << apply(triple,a1) << std::endl;	//non-memeber function apply() does not change matrix's elements

	std::cout << "Original matrix unaltered:\n" << a1 << std::endl;

	a1.apply(triple);	//member function apply() changes matrix's elements
	std::cout << "Modified matrix:\n" << a1 << std::endl;

	//exercise 2
	//create function object triple and apply to matrix 2 ways
	std::cout << "\nInitial values:\n" << a1 << std::endl;

	std::cout << "copy of modified matrix:\n" << apply(Triple1(), a1) << std::endl;	//non-memeber function apply() does not change matrix's elements

	std::cout << "Original matrix unaltered:\n" << a1 << std::endl;

	a1.apply(Triple1());	//member function apply() changes matrix's elements
	std::cout << "Modified matrix:\n" << a1 << std::endl;

	return 0;
}