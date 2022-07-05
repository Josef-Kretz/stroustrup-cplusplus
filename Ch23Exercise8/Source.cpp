//chapter 23 exercise 8
//user inputs file name and regex pattern
//search input file using input regex pattern

#include <iostream>
#include <fstream>

#include <regex>

#include <string>

using namespace std;

bool pattern_check(const string& user_string, regex& good_pattern)
//returns true if user_string is a good pattern
//places pattern into good_pattern
//otherwise return false
{
	try {
		good_pattern = user_string;
		return true;
	}
	catch (regex_error)
	{
		cerr << "Invalid pattern submitted\n";
	}
	return false;
}

bool file_opener(const string& filename, ifstream& ifs)
//opens filename in ifs, returns true upon success
//if ifs{filename} fails, return false
{
	ifs.open(filename);
	if (ifs) return true;
	cout << "Invalid file \"" << filename << "\" provided\n";
	return false;
}

bool file_parsing(istream& is, const regex& pat)
//returns true if eof found successfully
//returns false when error, or if eof not found
{
	try 
	{
		unsigned int line_count = 0; //keeps track of line number
		for (string s; getline(is, s);)
		{
			++line_count;
			auto s_pat = std::sregex_iterator(s.begin(), s.end(), pat);//iterates for matches in line
			auto sp_end = std::sregex_iterator();

			while (s_pat != sp_end)
				//iterates through all matches of line
			{
				cout << "line " << line_count << ": " << s_pat->str() << endl;
				++s_pat;
			}
		}

		if (is.eof()) return true;//if is reaches eof, return true
		else return false;
	}
	catch (...)
	{
		return false;
	}
}

void userFileParser()
{
	cout << "Type \"exit\" to exit program.\n";

	//loops until user submits a proper filename
	string filename;
	ifstream ifs;
	do {
		cout << "Enter a file to parse:\t";
		getline(cin, filename);
		if (filename == "exit") exit(1);
	} while (!file_opener(filename, ifs));

	//loops until user submits a proper 
	string user_string;
	regex user_pattern;
	do {
		cout << "Enter a pattern to parse \"" << filename << "\":\n";
		getline(cin, user_string);
		if (user_string == "exit") exit(2);
	} while (!pattern_check(user_string, user_pattern));

	if (file_parsing(ifs, user_pattern)) cout << "File: \"" << filename << "\" parsed successfully\n";

}

int main()
{
	userFileParser();

	return 0;
}