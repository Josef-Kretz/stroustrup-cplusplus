#include <iostream>
#include <string>

using namespace std;

inline void simple_error(string s)
{
	cerr << "Error: " << s << endl;
	exit(1);
}

int main()
{
	cout << "Please enter the name of the addressed: ";
	string inputName;
	getline(cin, inputName);
	cout << "\nDearest " << inputName << ',' << endl;

	cout << "\nHow are you? I am well, though I do miss you. My cats are also well!";
	cout << "\nInput the name of a shared acquaintance: ";
	string user_friend;
	getline(cin, user_friend);

	cout << "How has " << user_friend << " been doing lately?\n";
	char friend_sex = 0;
	cout << "Input 'm' if your shared acquaintance is male, or 'f' if they are female: ";
	cin >> friend_sex;
	cin.ignore();

	if (friend_sex == 'm')
		cout << "Tell him hello for me!";
	if (friend_sex == 'f')
		cout << "Tell her hello for me!";

	int age;
	cout << "\nEnter the age of the addressed: ";
	cin >> age;
	cin.ignore();

	if (age <= 0 || age >= 110)
		simple_error("you're kidding!");
	if (age < 12)
		cout << "Next year you will be " << age++;
	if (age == 17)
		cout << "Next year you will be able to vote!";
	if (age >= 70)
		cout << "I hope you're enjoying retirement!";

	cout << endl << "Yours sincerely, \n\n Tim" << endl;
	

	return 0;
}