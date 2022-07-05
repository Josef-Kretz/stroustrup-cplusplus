//chapter 23 exercise 7
//take a file as input and search for credit card numbers

#include <iostream>
#include <fstream>
#include <sstream>

#include <regex>

#include <string>

using namespace std;

bool num_check(const string& s)
//uses Luhn formula to check for a valid cc number
// sum all but last digit, modulus result, compare to last digit
{
	vector<int> vi;

	for (char c : s)
		if (isdigit(c))
			vi.push_back(c-'0');

	//last digit is a "check" number
	int lastDigit = vi[vi.size() - 1];
	vi.pop_back();

	unsigned int sum = 0;
	for (int i : vi)
		sum += i;

	if (sum % 10 == lastDigit)
		return true;

	return false;
}

void card_scraper(istream& is)
{
	regex cnum{ R"((\d\s*){16})" };

	unsigned int line_num = 0;

	for (string s; getline(is, s);)
	{
		++line_num;

		auto cnum_begin = std::sregex_iterator(s.begin(), s.end(), cnum);
		auto cnum_end = std::sregex_iterator();

		while (cnum_begin != cnum_end)
		{
			string ss = cnum_begin->str();
			if(num_check(ss))
				cout << " line-number: " << line_num << " CC#: " << ss << endl;
			++cnum_begin;
		}
	}
}


int main()
{
	string filename = "cards.txt";
	ifstream ifs{ filename };
	if (!ifs) throw runtime_error(filename + " inaccessible");

	card_scraper(ifs);
	if (num_check("4416     2470 71969 213"))
		cout << "Check successful\n";
}