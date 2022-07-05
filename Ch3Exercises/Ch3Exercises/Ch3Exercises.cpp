#include <iostream>
#include <string>

using namespace std;

void MilesToKm()
{
	cout << "Enter the distance in miles: ";
	double miles;
	cin >> miles;
	cin.ignore();
	cout << endl << miles << " miles it equal to " << (miles * 1.609) << " kilometers." << endl;
}


void compareNums()
{
	double num1, num2;
	cout << "Enter two numbers:\n";
	cin >> num1 >> num2;

	if (num1 < num2)
		cout << num2 << " is larger, " << num1 << " is smaller\n";
	else if (num2 < num1)
		cout << num1 << " is larger, " << num2 << " is smaller\n";
	else
		cout << num1 << " = " << num2;

	cout << "Sum: " << num1 + num2 << endl
		<< "Product: " << num1 * num2 << endl
		<< "Difference: " << num1 - num2 << endl
		<< "Ratio: " << num1/num2 << endl;

}

int main()
{

	//MilesToKm();
	compareNums();

	return 0;

}