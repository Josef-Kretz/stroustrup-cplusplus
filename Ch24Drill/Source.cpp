//chapter 24 drill: Numerics

#include <iostream>

#include "Matrix.h"

#include <complex>
#include <numeric>

using namespace std;

void user_sqrt()
{
	try {
		errno = 0;

		cout << "Input an integer to find its square root: ";
		int userNum;
		double answer;

		cin >> userNum;
		if (!cin)
		{
			cin.clear();
			string s;
			getline(cin, s);
			return;
		}

		answer = sqrt(userNum);

		if (errno == 0) cout << answer << endl;
		else cout << userNum << " has no square root\n";
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
}

void catch_ints() {
	char check = 'n';
	do {
		user_sqrt();

		cout << "Would you like to continue?(Y/N)\n";
		cin >> check;
		check = tolower(check);
	} while (check == 'y');

}

double get_double()
{
	double d;

	while(true) {
		cout << "Enter a number: ";
		cin >> d;
		if (cin) return d;
		else
		{
			cin.clear();
			string s;
			getline(cin, s);
			cout << "Error! " << s << " is not a number\n";
		}
	}
	cerr << "Forced to exit after improper user input\n";
	exit(1);
}

void itemize_c(Numeric_lib::Matrix<double>& m)
//add 10 doubles to the matric, passed by reference
{
	for (int i = 0; i < m.size(); ++i)
	{
		m(i) = get_double();
	}
}

void multi_table()
{
	using namespace Numeric_lib;

	cout << "Enter two integers to generate the table:\n";
	int n, m;

	do {
		m = int(get_double());
		n = int(get_double());
		if (n < 1 || m < 1) cout << "Re-enter numbers with a value greater than 0\n";
	} while (n < 1 || m < 1);

	Matrix<int, 2> table(n+1, m+1);

	for (int i = 0; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			table(i, j) = i * j;

	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= m; ++j)
			cout << table(i, j) << '\t';
		cout << endl;
	}
}

void complex_d()
{
	using namespace Numeric_lib;

	Matrix<complex<double>> mcd(10);

	for (int i = 0; i < 10; ++i)
	{
		complex<double> d;
		cout << "Enter a double: ";
		cin >> d;
		if (cin) mcd(i) = d;
		else throw runtime_error("Complex number not provided: complex_d()");
	}

	complex<double> total = 0;
	for (complex<double>* cd = &mcd(0); cd != &mcd(9) + 1; ++cd) total += *cd;
	cout << "Total of input complex numbers: " << total.real() << endl;
}

int main() {
	using namespace Numeric_lib;

	cout << "Size of:\n" << "char: " << sizeof(char) << "\nshort: " << sizeof(short) << "\nint: " << sizeof(int)
		<< "\nlong: " << sizeof(long) << "\nfloat: " << sizeof(float) << "\ndouble: " << sizeof(double)
		<< "\nint* : " << sizeof(int*) << "\ndouble* : " << sizeof(double*) << endl;

	Matrix<int> a(10); Matrix<int> b(100); Matrix<double> c(10); Matrix<int, 2> d(10, 10);
	Matrix<int, 3> e(10, 10, 10);
	cout << "\nSize of:\n" << "Matrix<int> a(10): " << sizeof(a) << "\nMatrix<int> b(100): " << sizeof(b) << "\nMatrix<double> c(10): " << sizeof(c)
		<< "\nMatrix<int, 2> d(10,10): " << sizeof(d) << "\nMatrix<int,3> e(10,10,10): " << sizeof(e) << endl;

	cout << "\n# of Elements:\n" << "Matrix<int> a(10): " << a.size() << "\nMatrix<int> b(100): " << b.size() << "\nMatrix<double> c(10): " << c.size()
		<< "\nMatrix<int, 2> d(10,10): " << d.size() << "\nMatrix<int,3> e(10,10,10): " << e.size() << endl;

	//catch_ints(); //take int from user, output sqrt(int) if possible


	//itemize_c(c);
	
	/*for (double* d = &c(0); d != &c(c.size());++d)
		cout << *d << endl;*/

	//multi_table();	//take two numbers and print out a multiplication table using matrixes

	
	//complex_d();	//read 10 complex doubles into a matrix and output the sum

	Matrix<int, 2> mm(2, 3);
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 3; ++j)
			mm(i, j) = int(get_double());

	for (int* i = &mm(0, 0); i != &mm(1, 2) + 1; ++i) cout << *i << '\t';
	cout << endl;

	return 0;
}