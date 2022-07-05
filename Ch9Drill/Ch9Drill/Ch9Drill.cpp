#include <iostream>

using namespace std;

enum class Month {
	jan =1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month operator++(Month& m)
{
	m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
	return m;
}

class Date {
private:
	int year;
	Month month;
	int day;

public:
	Date();
	Date(int y, Month m, int d);
	void add_day(int n);

	int years() const { return year; }
	Month months() const { return month; } 
	int days() const { return day; }
};

const Date& default_date()
{
	static Date dd{ 1990, Month::jan, 1 };
	return dd;
}

Date::Date()
	:year{ default_date().years() }, month{ default_date().months() }, day{ default_date().days() } 
{}

Date::Date(int y, Month m, int d)
{
	if (d < 1 || d>31) throw runtime_error("Date initialization error: day parameter");

	year = y;
	month = m;
	day = d;
}

void Date::add_day(int n)
{
	if (month == Month::dec && day+n > 31)
	{
		year += 1;
		++month;
		day = day + n - 31;
		return;
	}
	if (day+n > 31)
	{
		++month;
		day = day + n - 31;
		return;
	}
	day += n;
}

ostream& operator <<(ostream& os, const Date& d)
{
	return os << '(' << d.years() << ',' << int(d.months()) << ',' << d.days() << ')';
}

int main()
{
	try {
		Date today(1978, Month::jun, 25);
		Date tomorrow = today;
		tomorrow.add_day(1);

		cout << today << endl << tomorrow << endl;

		Date test = Date(); 
		
		cout << test;
	}
	catch (runtime_error& e) {
		cout << endl << "Error: " << e.what() << endl;
	}


	

	return 0;
}