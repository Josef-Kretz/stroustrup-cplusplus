#pragma once
#include <iostream>

namespace Chrono {

	enum class Month {
		jan = 1, feb, mar, apr, may, jun, july, aug, sep, oct, nov, dec
	};

	class Date {
	public:
		class Invalid {}; //to throw as an exception

		Date(int y, Month m, int d); //check for valid date and initialize
		Date();						// default constructor
		//default copy operation is acceptable

		//non-modifying operations
		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }

		//modifying operations
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);

	private:
		int y;
		Month m;
		int d;
	};

	bool is_date(int y, Month m, int d); //true for valid date

	bool leapyear(int y);

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	std::ostream& operator<<(std::ostream& os, const Date& d);
	std::istream& operator>>(std::istream& is, Date& dd);

	//Day day_of_week(const Date& d); //day of week d
	Date next_Sunday(const Date& d); //next sunday after d
	Date next_weekday(const Date& d); //next weekday after d
}//chrono