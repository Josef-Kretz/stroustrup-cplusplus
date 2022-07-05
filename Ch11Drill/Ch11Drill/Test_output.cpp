#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	int birth_year = 1993;

	cout << "Decimal\t" << "\tHexadecimal\t" << "Octal" << endl;
	cout << showbase << dec << birth_year << "\t\t" << hex << birth_year << "\t\t" << oct << birth_year << endl;
	cout << dec << 26 << endl;

	cout << "Try reading as octal, hexadeicmal, etc...\n";
	int a, b, c, d;
	cin >> a >> oct >> b >> hex >> c >> d;
	cout << a << "\t" << b << '\t' << c << '\t' << d << endl;

	double num = 1234567.89;

	cout << defaultfloat << num <<'\t' << fixed << num <<'\t' << scientific << num << endl;

	vector <string> fname{ "Jo", "Jane", "Jimmy", "John", "Yonny" };
	vector<string> lname{ "Jameson", "Johnston", "Hendy", "Johnny", "Wix" };
	vector<string> pnum{ "988-2300", "654-1237", "657-9800","877-2600","230-0087" };
	vector<string> email{ "JoJ@gmail.ca", "JaneJo@gmail.ca","JimmyH@gmail.ca", "jojonnyjonny@gmail.ca", "yonjohn@gmail.ca" };

	cout << setw(15) << "First Name\t" << setw(15) << "Last Name\t" << setw(15) << "Phone Number\t" << setw(25) << "E-mail\n";
	for (int i = 0; i < fname.size(); ++i)
	{
		cout << setw(15) << fname[i] << setw(15) << lname[i] << setw(15) 
			<< pnum[i] <<'\t' << setw(25) << email[i] << endl;
	}

	return 0;
}