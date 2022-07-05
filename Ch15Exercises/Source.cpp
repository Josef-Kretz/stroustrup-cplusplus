#include "Simple_window.h"
#include "Graph.h"

using namespace std;

double fac1(double n) { return n > 1 ? n * fac1(n - 1) : 1; }		//factorial n!, recursive function

double fac2(double n)		//factorial n!, iterative function
{
	double r = 1;
	while (n > 1)
	{
		r *= n;
		--n;
	}
	return r;
}

class Function2 : public Shape
{
public:
	Function2(Fct ff, double r1, double r2, Point orig,
		int count = 100, double xscale = 25, double yscale = 25, int precision = 5)
		: f(ff), rOne(r1), rTwo(r2), origin(orig), cCount(count),
		x_scale(xscale), y_scale(yscale), pPrecision(precision)
		//graph f(x) for x in [r1:r2] using count line segments with (0,0) displayed a origin
		//x coordinates are scaled by scale and y by yscale
	{
		if (rTwo - rOne <= 0) throw runtime_error("Bad graphing range");
		if (cCount <= 0) throw runtime_error("Non-positive graphing count");

		double dist = (rTwo - rOne)/cCount;
		double r = rOne;
		for (int i = 0; i < cCount; ++i)
		{
			add(Point{ origin.x + int(r * x_scale), origin.y - int(f(r) * y_scale) });
			r += dist;
		}
		set_color(Color::black);
	}

	void reset()
	{
		
		clear_points();
		
		double d = (rTwo - rOne) / cCount;
		double r = rOne;

		for (int i = 0; i < cCount; ++i)
		{
			add(Point{ origin.x + int(r * x_scale), origin.y - int( f(r) * y_scale) });
			r += d;
		}
	}

	void set_range(int rr1, int rr2) { rOne = rr1; rTwo = rr2; reset();	}
	void set_count(int c) { cCount = c; reset();	}
	void set_xscale(double x) { x_scale = x; reset();	}
	void set_yscale(double y) { y_scale = y; reset();	}
	void set_center(Point p) { origin = p; reset();	}
	void set_fct(Fct nF) { f = nF; reset();	}
	void set_precision(int pp) { pPrecision = pp; reset();	}


private:
	double rOne, rTwo, x_scale, y_scale;
	int cCount, pPrecision;
	Fct* f;
	Point origin;
};

double Leibniz(double x)
{
	double sum = 1;		//beginning value in Leibniz's formula
	double denom = 3;	//first term's denominator, incremented by 2
	bool flip = true;
	for (double d = 0; d < x; ++d)
	{
		double fraction = 1.0 / (denom + (d * 2));
		flip ? sum -= fraction : sum += fraction;
		flip = !flip;
	}
	cout << sum << endl;
	return sum;
}

class Bar_Graph : public Shape
{
public:
	Bar_Graph(Point p, int xlength, int ylength, int xscale, int yscale)
		:origin(p),
		x(Axis::x,p, xlength, xlength/xscale, "x axis"),
		y(Axis::y, p, ylength, ylength/yscale, "y axis"),
		x_length(xlength), y_length(ylength), x_scale(xscale), y_scale(yscale),
		title(origin, "")
	{
		xnotch = xlength / xscale;
		//move x axis label to near the x axis
		Point xp = x.label.point(0);
		x.label.move(origin.x - xp.x, 0);

		set_color(Color::black);
	}


	void draw_lines() const
	{
		x.draw_lines();
		y.draw_lines();

		title.draw_lines();

		for (int i = 0; i < n_values.size(); ++i)
		{
			int x1 = origin.x + (x_scale * i);
			int y1 = origin.y - n_values[i];
			int x2 = x1 + x_scale;
			int y2 = origin.y;

			Graph_lib::Rectangle r(Point{ x1, y1 }, Point{ x2, y2 });
			r.set_color(user_color);
			r.draw_lines();

			Point r_text{ int(x2-(x_scale/2)), int((y1+y2) / 2) };
			Text r_label(r_text, n_labels[i]);
			r_label.set_color(user_color);
			r_label.draw_lines();
		}

		
	}

	void add(int value, string s="")
	{
		value = int(value * y_scale);
		if (value >= 0)
		{
			n_values.push_back(value);
			n_labels.push_back(s);
		}
	}

	void set_color(Color c)
	{
		user_color = c;
		Shape::set_color(c);
		
		//set X axis colours
		x.set_color(c);
		x.label.set_color(c);
		x.notches.set_color(c);
		//set Y axis colours
		y.set_color(c);
		y.label.set_color(c);
		y.notches.set_color(c);
		//bar section and bar labels set in draw_lines()
	}

	void set_title(const string& s)
	{
		title.move(int(x_length / 2), int(y_length + 10) * (-1));
		title.set_label(s);
		title.set_color(user_color);
	}

	void set_x_label(const string& s) { x.label.set_label(s); }
	
	void set_y_label(const string& s) { y.label.set_label(s); }
private:
	vector<double> n_values;
	vector<string> n_labels;
	Point origin;
	Axis x, y;
	int x_length, y_length, x_scale, y_scale;
	int xnotch;
	Text title;
	Color user_color = Color::black;
};

int main()
{
	/*	//chapter 15 exercise 1
	cout << setprecision(20) << fac1(20) << endl
		<< fac2(20) << endl;*/
	/*try {
		//chapter 15 exercise 2
		Simple_window win(Point{ 100,100 }, 800, 500, "Chapter 15 Exercises");

		Function2 testF([](double x) -> double { return 1; }, -10, 10, Point{ 400, 250 });

		win.attach(testF);
		win.wait_for_button();


		testF.set_color(Color::red);
		testF.set_center(Point{ 400, 50 });

		win.wait_for_button();


		testF.set_range(1, 2);
		testF.set_color(Color::blue);

		win.wait_for_button();
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}*/

	/*	//chapter 15 exercise 4, Graphing Multiple Functions
	try {
		//window size
		constexpr int xmax = 800;
		constexpr int ymax = 500;
		//center point of window
		constexpr int x_origin = xmax / 2;
		constexpr int y_origin = ymax / 2;
		Point origin{ x_origin, y_origin };
		//min,max range, # of points, x,y scaling
		constexpr int r_min = -10;
		constexpr int r_max = 11;
		constexpr int n_points = 400;
		constexpr int x_scale = 40;
		constexpr int y_scale = 40;


		constexpr int xlength = xmax - 40;
		constexpr int ylength = ymax - 40;

		Simple_window win(Point{ 100,100 }, xmax, ymax, "Exercise 4");
		//create graphing axes
		Axis x(Axis::x, Point{ 20, y_origin }, xlength, xlength / x_scale, "1 notch = 10 pixels");
		Axis y(Axis::y, Point{ x_origin, ylength + 20 }, ylength, ylength / y_scale, "1 notch = 10 pixels");

		//defining functions sine, cos, sin+cos, sin^2+cos^2
		Function f1(sin, r_min, r_max, origin, n_points, x_scale, y_scale);
		Function f2(cos, r_min, r_max, origin, n_points, x_scale, y_scale);
		Function f3([](double x) -> double {return cos(x) + sin(x); },
			r_min, r_max, origin, n_points, x_scale, y_scale);
		Function f4([](double x) -> double { return (cos(x) * cos(x)) + (sin(x) * sin(x)); },
			r_min, r_max, origin, n_points, x_scale, y_scale);

		x.set_color(Color::black); y.set_color(Color::black); 
		f1.set_color(Color::black); f2.set_color(Color::black);
		f3.set_color(Color::black); f4.set_color(Color::black); 

		win.attach(x);
		win.attach(y);
		win.attach(f1);
		win.attach(f2);
		win.attach(f3);
		win.attach(f4);

		win.wait_for_button();

	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}*/
	
		/*//chapter 15 exercise 5
	try {
		//window size
		constexpr int xmax = 800;
		constexpr int ymax = 500;
		//center point of window
		constexpr int x_origin = xmax / 2;
		constexpr int y_origin = ymax / 2;
		Point origin{ x_origin, y_origin };
		//min,max range, # of points, x,y scaling
		constexpr int r_min = -1;
		constexpr int r_max = 1;
		constexpr int n_points = 400;
		constexpr int x_scale = 5;
		constexpr int y_scale = 200;


		constexpr int xlength = xmax - 40;
		constexpr int ylength = ymax - 40;

		Simple_window win(Point{ 100,100 }, xmax, ymax, "Exercise 4");
		//create graphing axes
		Axis x(Axis::x, Point{ 20, y_origin }, xlength, xlength / x_scale, "1 notch = 10 pixels");
		Axis y(Axis::y, Point{ x_origin, ylength + 20 }, ylength, ylength / y_scale, "1 notch = 10 pixels");
		x.set_color(Color::black);
		y.set_color(Color::black);

		win.attach(x);
		win.attach(y);

		Open_polyline leib;
		leib.set_color(Color::red);
		leib.add(Point{ x_origin, int(y_origin - (1*y_scale)) });
		win.attach(leib);

		for (int i = 0; i < 5000; i += 1)
		{
			//set new label for each new iteration
			ostringstream ss;
			ss << "Leibniz Approximation Iteration: " << i + 1;
			win.set_label(ss.str());
			//get next approximation
			double xx = double(x_origin + (i*x_scale));
			double yy = y_origin - (Leibniz(i)*y_scale);
			leib.add(Point{int(xx), int(yy) });
			win.wait_for_button();
			if (int(i * x_scale) >= xlength / 2) break; //limits function to graph space
		}
		win.wait_for_button();
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}*/

		//chapter 15 exercise 6, 7
try {
	//window size
	constexpr int xmax = 800;
	constexpr int ymax = 500;
	//center point for graph axes
	constexpr int x_origin = xmax / 2;
	constexpr int y_origin = ymax / 2;
	Point origin{ x_origin, y_origin };
	//axes length
	constexpr int xlength = 400;
	constexpr int ylength = 400;
	//scaling and # of points
	constexpr int x_scale = 20;
	constexpr int y_scale = 20;
	constexpr int n_points = 400;
	//range of values (min, max)
	constexpr int r_min = -10;
	constexpr int r_max = 11;


	Simple_window win(Point{ 100,100 }, xmax, ymax, "Bar Graphs: Exercise 6 and 7");
	//create X axis and Y axis
	Bar_Graph testBG(Point{ 25, ymax - 25 }, 600, 400, 50, 15);
	win.attach(testBG);

	win.wait_for_button();

	testBG.add(10, "Hi");
	testBG.add(5);
	testBG.add(20, "Cool");

	win.wait_for_button();

	testBG.set_color(Color::dark_green);
	testBG.set_title("Pep with Step");
	testBG.set_x_label("Number of Steps");
	testBG.set_y_label("Level of Pep");


	win.wait_for_button();
	
	testBG.add(23);
	testBG.add(40, "Super");
	testBG.add(55);
	testBG.add(22, "Duper");
	
	win.wait_for_button();
}
catch (runtime_error& e)
{
	cerr << "Error: " << e.what();
}

	return 0;
}