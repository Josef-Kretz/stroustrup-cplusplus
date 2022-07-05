//chapter 24, exercise 4: get the Gaussian elimination program to work

#include <iostream>

#include "Matrix.h"
#include "MatrixIO.h"

#include <random>
#include <limits>

using namespace std;

using Matrix = Numeric_lib::Matrix<double, 2>;
using Vector = Numeric_lib::Matrix<double, 1>;
using Index = Numeric_lib::Index;

void classical_elimination(Matrix& A, Vector& b)
{
	const Index n = A.dim1();

	//traverse from 1st column to the next to lat
	//filling zeroes into all elements under the diagonal

	for (Index j = 0; j < n - 1; ++j)
	{
		const double pivot = A(j, j);
		if (pivot == 0) throw runtime_error("Class_elim fail, pivot = 0");

		//fill zeroes into each element under the diagonal of the ith row
		for (Index i = j + 1; i < n; ++i)
		{
			const double mult = A(i, j) / pivot;
			//A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));//ex6 replace with loop

			b(i) -= mult * b(j);	//make the coressponding change to b
		}
			
	}
}

Vector back_substitution(Matrix& A, const Vector& b)
{
	const Index n = A.dim1();
	Vector x(n);

	for (Index i = n - 1; i >= 0; --i)
	{
		double s = b(i) - dot_product(A[i].slice(i + 1), x.slice(i + 1));

		if (double m = A(i, i)) x(i) = s / m;
		else throw runtime_error("Back_subst fail " + i);
	}
	return x;
}

void elim_with_partial_pivot(Matrix& A, Vector& b)
{
	const Index n = A.dim1();

	for (Index j = 0; j < n; ++j)
	{
		Index pivot_row = j;

		//look for a suitable picot
		for (Index k = j + 1; k < n; ++k)
			if (abs(A(k, j)) > abs(A(pivot_row, j))) pivot_row = k;

		//swap the rows if we found a better pivot
		if (pivot_row != j)
		{
			A.swap_rows(j, pivot_row);
			std::swap(b(j), b(pivot_row));
		}

		//elimination
		for (Index i = j + 1; i < n; ++i)
		{
			const double pivot = A(j, j);
			if (pivot == 0) throw runtime_error("can't solve: pivot == 0");
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);
		}
	}
}

Vector classical_gaussian_elimination(Matrix A, Vector b)
{
	classical_elimination(A, b);
	return back_substitution(A, b);
}

Vector operator*(const Matrix& m, const Vector& u)
{
	const Index n = m.dim1();
	Vector v(n);
	for (Index i = 0; i < n; ++i) v(i) = dot_product(m[i], u);
	return v;
}

Vector random_vector(Index n)
{
	Vector v(n);
	default_random_engine ran{};	//generates integers
	uniform_real_distribution<> unreal{ 0, 100 };	//maps ints into doubles in [0:max)

	for (Index i = 0; i < n; ++i)
		v(i) = unreal(ran);

	return v;
}

Matrix random_matrix(Index n)
{
	Matrix m(n,n);
	default_random_engine ran{};	//generates integers
	uniform_real_distribution<> unreal{ 0, 100};	//maps ints into doubles in [0:max)

	for (int i = 0; i < n*n; ++i)
	{
		auto p = &m(0, 0) + i;
		*p = unreal(ran);
	}

	return m;
}

void solve_random_system(Index n)
{
	Matrix A = random_matrix(n); //see §24.7
	Vector b = random_vector(n);

	cout << "A=" << A << endl;
	cout << "b=" << b << endl;

	try {
		Vector x = classical_gaussian_elimination(A, b);
		cout << "classical elim solution is x = " << x << endl;
		Vector v = A * x;
		cout << "A*x = " << v << endl;
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
	}
}

int main()
{
	//solve_random_system(5); //exercise 4, get program to work
	solve_random_system(10); //exercise 6, replace dot_product() and scale_and_add() with loops

	//exercise 5, throws error unless elim_with_partial_pivot() is used
	Matrix A1(2, 2);
	A1(0, 0) = 0;
	A1(0, 1) = 1;
	A1(1, 0) = 1;
	A1(1, 1) = 0;
	cout << A1 << endl;

	Vector b1(2);
	b1(0) = 5;
	b1(1) = 6;
	cout << b1 <<endl;

	try {

		//Vector x = classical_gaussian_elimination(A1, b1);	//fails to solve

		//using function elim_with_partial_pivot() moves the zeroes so classical_gaus can solve
		elim_with_partial_pivot(A1, b1);
		Vector x = classical_gaussian_elimination(A1, b1);
		cout << "elim + classical elim solution is x = " << x << endl;
		Vector v = A1 * x;
		cout << "A1*x = " << v << endl;
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}

	return 0;
}