#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int not_a_reading = -7777; //less than absolute zero
const int not_a_month = -1;
constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

struct Reading
{
	int day;
	int hour;
	double temperature;
};
struct Day
{
	vector<double> hour{ vector<double>(24,not_a_reading) };
};
struct Month //a month of temperature readings
{
	int month{ not_a_month }; //[0:11] January is 0
	vector<Day> day{ 32 }; //[1:31] on vector of readings per day
};
struct Year
{
	int year; // positive == AD
	vector<Month> month{ 12 }; //[0:11] January is 0
};

bool is_valid(const Reading& r) //rough test for validity
{
	if (r.day < 1 || r.day>31) return false;
	if (r.hour < 0 || r.hour>23) return false;
	if (r.temperature<implausible_min || r.temperature>implausible_max) return false;

	return true;
}

void end_of_loop(istream& ist, char term, const string& message)
{
	if (ist.fail())
	{
		ist.clear();
		char ch;
		if(ist >> ch && ch == term) return; //all is fine
		throw runtime_error(message);
	}
}


vector<string>month_input_tbl = {
	"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
};

int month_to_int(string s)
//is s the name of a month? return index[0:11] is true, return -1 is false
{
	for (int i = 0; i < 12; ++i)
		if (month_input_tbl[i] == s)
			return i;

	throw runtime_error("Month to int fail, month not found\n");
}

vector<string> month_print_tbl = {
	"January", "February", "March", "April", "May", "June", "July", "August", "September",
	"October", "November", "December"
};

string int_to_month(int i)
//months[0:11]
{
	if (i < 0 || i > 11) throw runtime_error("Bad month integer input\n");
	return month_print_tbl[i];
}


istream& operator>>(istream& is, Reading& r)
{
	//read a temperature reading from is into r
	//format (3 4 9.7 )
	//check format, don't check data validity

	char ch1;
	if (is >> ch1 && ch1 != '(') //could it be a Reading?
	{
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	char ch2;
	int d, h;
	double t;
	is >> d >> h >> t >> ch2;

	if (!is || ch2 != ')') throw runtime_error("Bad reading\n");

	r.day = d;
	r.hour = h;
	r.temperature = t;

	return is;
}

istream& operator>>(istream& is, Month& m)
//read a month from is into m
//format { month feb... }
{
	char ch = 0;
	if (is >> ch && ch != '{')
	{
		is.unget();
		is.clear(ios_base::failbit); //we failed to read a month
		return is;
	}

	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month") throw runtime_error("Bad start of month\n");
	m.month = month_to_int(mm);

	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r;)
	{
		if (is_valid(r))
		{
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else
			++invalids;
	}

	if (invalids) throw runtime_error("Invalid readings in month\n");
	if (duplicates) throw runtime_error("Duplicate readings in month\n");
	end_of_loop(is, '}', "Bad end of month\n");

	return is;
}

istream& operator >>(istream& is, Year& y)
//read a year from is into y
//format { year 1972...}
{
	char ch;
	is >> ch;
	if (ch != '{')
	{
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year") throw runtime_error("Bad start of year\n");

	y.year = yy;

	while (true)
	{
		Month m; //re-declare month each time
		if (!(is >> m)) break;
		y.month[m.month] = m;
	}

	end_of_loop(is, '}', "Bad end of year\n");
	return is;
}

void print_year(ofstream& ofs, Year& y)
{
	ofs << "{" << " year " << y.year;

	for (Month m : y.month)
	{
		if (m.month != not_a_month)
			ofs << endl << "{" << " month " << int_to_month(m.month);

		for (int days = 1; days < m.day.size();++days)
		{
			if (m.month == not_a_month) break;

			for (int hours = 0; hours < m.day[days].hour.size(); ++hours)
			{
				int temperature = m.day[days].hour[hours];
				if (temperature == not_a_reading) break;

				//				day				hour			temperature
				ofs << endl << "( " << days << " " << hours << " " << m.day[days].hour[hours] << " )";
			}
		}
		if(m.month != not_a_month)
			ofs << "}" << endl;

	}

	ofs << '}' << endl;
}

int main()
{
	try {
		//open an input file:
		cout << "Please enter input filename\n";
		string iname;
		cin >> iname;
		ifstream ifs{ iname };
		if (!ifs) throw runtime_error("Can't open input file " + iname);

		ifs.exceptions(ifs.exceptions() | ios_base::badbit); //throw for bad()

		//open an output file:
		cout << "Please enter output  filename\n";
		string oname;
		cin >> oname;
		ofstream ofs{ oname };
		if (!ofs) throw runtime_error("Can't open output file " + oname);


		//read an arbitrary number of year:
		vector<Year> ys;
		while (true)
		{
			Year y;
			if (!(ifs >> y)) break;
			ys.push_back(y);
		}
		cout << "Read " << ys.size() << " years of readings.\n";

		for (Year& y : ys) print_year(ofs, y);
	}
	catch (runtime_error& e)
	{
		cout << "Error " << e.what() << endl;
	}

	return 0;
}