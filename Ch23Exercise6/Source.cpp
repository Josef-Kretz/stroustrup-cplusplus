//chapter 23 exercise 6
//write a program that finds DATEs in a text file
//output the dates with their line number
//ex: line-number: date

#include <iostream>
#include <fstream>

#include <regex>

#include <string>

using namespace std;

void date_scraper(ifstream& ifs)
{
	regex date1{ R"((([0-1]?\d/[0-3]?\d/([1-2]\d)*'?\d{2})|([[:alpha:]]{3,8}\s*[0-3]?[0-9]\s*(st|nd|rd|th)?\s*,?\s*([1-2]\d)?'?\d{2})))" };

	unsigned int line_count = 0;
	for (string s; getline(ifs, s);)
	{
		++line_count;	//keeps track of lines
		
		auto dates_begin = std::sregex_iterator(s.begin(), s.end(), date1);
		auto dates_end = std::sregex_iterator();

		while (dates_begin != dates_end)
			//dates_begin holds current match, advances until no more matches
		{
			cout << "line-number " << line_count << " DATE: " << dates_begin->str() << endl;
			++dates_begin;
		}
	}
}

int main()
{
	string filename = "dates.txt";
	ifstream ifs{ filename };

	date_scraper(ifs);

	return 0;
}