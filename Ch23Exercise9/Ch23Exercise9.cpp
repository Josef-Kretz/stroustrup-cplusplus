//chapter 23 exercise 9, 10
//re-coding §23.9 Table Checking Program to use istream.eof()

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <regex>

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace Grade {
	enum class Grade { zero, one, two, three, four, five, size, seven, eight, nine, ten };

	ostream& operator<<(ostream& os, Grade gr)
	{
		return os << int(gr);
	}
}

bool converts_to_int(string s)
//tests if string will throw with stoi
{
	istringstream is{ s };
	int i;
	if (is >> i) return true;
	return false;
}

struct ClassGrades
	//contains # of boys, # of girls, and total
{
	ClassGrades(string noot="") :note(noot) {}
	ClassGrades(int b, int g, int t, string knote = "" ):boys(b), girls(g), total(t), note(knote) {}
	unsigned int boys = 0;
	unsigned int girls = 0;
	unsigned int total = 0;
	string note;
};

ostream& operator<<(ostream& os, map<Grade::Grade, ClassGrades> m)
//output Grade# boys# girls# total#
{
	char t = '\t';
	int w = 30;
	for (auto p = m.begin(); p != m.end(); ++p)
	{
		os <<setw(5)<< p->first << setw(w) << p->second.boys << setw(w) << p->second.girls << setw(w) << p->second.total << endl;
	}
	return os;
}

bool construct_table(ostream& os, const map<Grade::Grade, ClassGrades>& grM, const map<string, ClassGrades>& altM)
//grM contains amalgamated class numbers, altM contains REST and TOTAL LINE data
//try to construct a new table with provided data, return true if successful
/*format:
* <header line>
* <rows of data>
* <total data line> */

{
	//header line, "header"
	auto p = altM.begin();
	while (p != altM.end() && p->second.note != "header") ++p;
	if (p->second.note != "header") throw runtime_error("Header not found: construct_table()");
	os << p->first << endl;

	//data rows:
	os << grM;

	int w = 20; //used for spacing/formatting
	//remainder numbers outside of a grade, "rest"
	p = altM.begin();
	while (p != altM.end() && p->second.note != "rest") ++p;
	if (p->second.note != "rest") throw runtime_error("Rest row/Remainder row not found: construct_table()");
	os << p->first << setw(w) << p->second.boys << setw(28) << p->second.girls << setw(26) << p->second.total << endl;

	//total line, "total"
	p = altM.begin();
	while (p != altM.end() && p->second.note != "total") ++p;
	if (p->second.note != "total") throw runtime_error("Total row not found: construct_table()");
	os << p->first << setw(w) << p->second.boys << setw(w) << p->second.girls << setw(30) << p->second.total << endl;

	return true;
}

bool output_file(string filename, map<Grade::Grade, ClassGrades> grM, map<string,ClassGrades> altM)
//open ofstream with filename, pass ofstream and data maps to construct_table
//return true if successful
{
	ofstream ofs{ filename };
	if (!ofs) throw runtime_error(filename + " cannot be opened");
	if (construct_table(ofs, grM, altM)) return true;
	return false;
}

int main()
{
	try {
		ifstream in{ "table.txt" }; //input file
		if (!in) throw runtime_error("no input file");

		string line;	//input buffer
		int lineno = 0;

		regex header{ R"(^[\w]+(\s*[\w]+)*\s*$)" };	//header line
		regex row{ R"(^\s*([\w]+\s*[[:alpha:]]*)\s*(\d+)\s*(\d+)\s*(\d+)$)" };	//data line

		map<Grade::Grade, ClassGrades> org_chart;//stores graded row data
		map<string, ClassGrades> alt_lines;//stores header, total, and ungraded data

		if (getline(in, line)) //check header line
		{
			smatch matches;
			if (!regex_match(line, matches, header)) throw runtime_error("No header line found");
			alt_lines.insert(make_pair(matches[0], ClassGrades("header")));
		}

		//column totals
		int boys = 0;
		int girls = 0;


		while (getline(in, line))
		{
			++lineno;
			smatch matches;
			if (!regex_match(line, matches, row)) throw runtime_error("bad line " + to_string(lineno));

			if (in.eof()) cout << "at eof\n";

			//check row:
			int curr_boy =stoi(matches[2]);
			int curr_girl = stoi(matches[3]);
			int curr_total = stoi(matches[4]);

			if (curr_boy + curr_girl != curr_total) throw runtime_error("Bad row calculation");

			

			if (matches[1].str().length() > 10) //last line
			{
				if (curr_boy != boys) throw runtime_error("boys don't add up");
				if (curr_girl != girls) throw runtime_error("girls don't add up");
				if (!(in >> ws).eof()) throw runtime_error("characters after Total line");
				alt_lines.insert(make_pair(matches[1], ClassGrades(boys, girls, boys+girls,"total")));
				
				//call function to construct and output table to a txt file
				string outfile = "constructed_table.txt";
				if (output_file(outfile, org_chart, alt_lines));
				else cerr << "New table could not be constructed and saved";

				//end program
				return 0;
			}
			else if (converts_to_int(matches[1]))
			{
				//add int values to map, grade as key
				int gr = stoi(matches[1]);
				if (gr < 0 || gr > 10) throw runtime_error("Invalid grade on table");
				Grade::Grade gkey = Grade::Grade(gr);

				auto gradep = org_chart.find(gkey);
				if (gradep != org_chart.end())
				{
					gradep->second.boys += curr_boy;
					gradep->second.girls += curr_girl;
					gradep->second.total += curr_total;
				}
				else {
					org_chart.insert(make_pair(gkey, ClassGrades(curr_boy, curr_girl, curr_total,"row")));
				}
			}
			else
				alt_lines.insert(make_pair(matches[1], ClassGrades(curr_boy, curr_girl, curr_total,"rest")));

			//update totals
			boys += curr_boy;
			girls += curr_girl;
		}
		throw runtime_error("Total line not found");	
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "Unkown error\n";
	}
}