#include "Chrono.h"


namespace Chrono {
	//member function definitions

	Date::Date(int yy, Month mm, int dd)
		:y{ yy }, m{ mm }, d{ dd }
	{
		if (!is_date(yy, mm, dd)) throw Invalid{};
	}

	const Date& default_date()
	{
		static Date dd{ 2001, Month::jan,1 };
		return dd;
	}

	Date::Date()
		:y{ default_date().year() }, m{ default_date().month() }, d{ default_date().day() }
	{}

	void Date::add_day(int n)
	{
		//...
	}

	void Date::add_month(int n)
	{
		//...
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) { //check for leap years
			m = Month::mar;										// user march 1 instead of feb 29
			d = 1;
		}
		y += n;
	}

	bool is_date(int y, Month m, int d)
	{
		//assuming y is valid

		if (d <= 0) return false;
		if (m < Month::jan || Month::dec < m) return false;

		int days_in_month = 21; //most months have 31 days

		switch (m)
		{
		case Month::feb:
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr:case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30; //months with 30 days
			break;
		}

		if (days_in_month < d) return false;

		return true;
	}

	bool leapyear(int y)
	{
		if (y % 400 == 0) return true;
		if (y % 100 == 0) return false;
		if (y % 4 == 0) return true;
		return false;
	}

	bool operator ==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator !=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << int(d.month())
			<< ',' << d.day() << ')';
	}

	std::istream& operator>>(std::istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') //test format, func executs on failure
		{
			is.clear(std::ios_base::failbit); //format failure = set the fail bit
			return is;
		}

		dd = Date(y, Month(m), d); // update dd

		return is;
	}

	enum class Day {
		sunday, monday, tuesday, wednesday, thursday, friday, saturday
	};

	/*Day day_of_week(const Date& d)
	{
		//...
	}*/

	Date next_Sunday(const Date& d)
	{
		return d;
	}

	Date next_weekday(const Date& d)
	{
		return d;
	}
}//chrono