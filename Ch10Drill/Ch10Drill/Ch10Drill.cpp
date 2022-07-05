#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Point
{
	int x, y;

	Point() {}
	Point(int xx, int yy) : x(xx), y(yy) {}
};

ostream& operator << (ostream & os, const Point & p)
{
	return os << '(' << p.x << ',' << p.y << ')';
}
istream& operator >> (istream& is, Point& p)
{
	char lbracket, comma, rbracket;
	int x, y;
	is >> lbracket >> x >> comma >> y >> rbracket; // ( x , y )

	if (!is) return is;
	if (lbracket != '(' || comma != ',' || rbracket != ')') //check formatting
	{
		is.clear(ios_base::failbit);
		return is;
	}
	p = Point(x, y);
	return is;
}

void skip_to_int()
{
	if (cin.fail())
	{
		cin.clear();
		for (char ch; cin >> ch;)
		{
			if (isdigit(ch) || ch == '-')
			{
				cin.unget();
				return;
			}
		}
		cout << "No integer found\n";
	}
}

Point get_int()
{
	cout << "Enter two points as integers:\n";
	int x = 0;
	int y = 0;

	while (true)
	{
		if (cin >> x) 
		{
			if (cin >> y)
				return Point(x, y);
		}
		skip_to_int();
	}
}

void OFPrint(const vector<Point> const & pvec)
{
	ofstream ofs { "mydata.txt" };
	if (!ofs) throw runtime_error("Can't open mydata.txt in OFPrint\n");
	for (Point p : pvec)
		ofs << p << endl;
}

vector<Point> IFPrint()
{
	vector<Point> readVec;
	ifstream ifs{ "mydata.txt" };
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	if (!ifs) throw runtime_error("Cannot access mydata.txt\n");
	for (Point p; ifs >> p;)
		readVec.push_back(p);

	if (ifs.bad()) throw runtime_error("Bad read from file mydata.txt\n");
	//if (ifs.fail()) throw runtime_error("Failed read");

	return readVec;
}
int main()
{
	vector<Point> original_points;
	char userTest = 'y';

	try {
		do
		{
			original_points.push_back(get_int());

			cout << "Would you like to add more?(Y/N)\n";
			cin >> userTest;
			userTest = tolower(userTest);
		} while (userTest == 'y');
	}
	catch (runtime_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	for (Point p : original_points)
		cout << p;
	vector<Point> accessed_points;

	try {
		OFPrint(original_points);		
		accessed_points = IFPrint();
	}
	catch (runtime_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}
	
	//original_points.push_back(Point()); //uncomment to force error
	bool  success = original_points.size() == accessed_points.size();

	if (!success) cout << "Something is wrong!\n";

	return 0;
}