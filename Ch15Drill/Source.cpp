#include "Simple_window.h"
#include "Graph.h"

using namespace std;

double sloping_cos(double x)
{
	return cos(x) + (x / 2);
}

int main()
{

	constexpr int xmax = 600;		//window dimension
	constexpr int ymax = 600;
	
	constexpr int x_origin = xmax / 2;		//position of (0,0) is center of window
	constexpr int y_origin = ymax / 2;
	const Point origin{ x_origin, y_origin };

	constexpr int r_min = -10;		//range of -10 to 11
	constexpr int r_max = 11;


	constexpr int n_points = 20;	//number of points used in range

	constexpr int x_scale = 20;		//scaling factors
	constexpr int y_scale = 20;

	Simple_window win(Point{ 100,100 }, xmax, ymax, "Function graphs");

	constexpr int xlength = 400;
	constexpr int ylength = 400;

	Axis x(Axis::x, Point{ 100, y_origin }, xlength, xlength/x_scale, "1 == 20 pixels");
	Axis y(Axis::y, Point{ x_origin, ylength + 100 }, ylength, ylength / y_scale, "1 == 20 pixels");
	x.set_color(Color::red);
	y.set_color(Color::red);

	win.attach(x);
	win.attach(y);

	Function s1{ [] (double x) -> double { return 1; }, 
		r_min, r_max, origin, 400, 20, 20 };
	s1.set_color(Color::black);

	Function s2{ [] (double x) -> double {return x / 2; },
	r_min, r_max, origin, 400, 20, 20 };
	s2.set_color(Color::black);

	Text slope2{ Point{80, s2.point(0).y}, "x/2" };
	slope2.set_color(Color::black);

	Function s3{ [] (double x) -> double { return x * x; },
	r_min, r_max, origin, 400, 20, 20 };
	s3.set_color(Color::black);

	Function s4{ cos, r_min, r_max, origin, 400, 20, 20 };
	s4.set_color(Color::blue);

	Function s5{ sloping_cos, r_min, r_max, origin, 400, 20, 20 };
	s5.set_color(Color::black);

	win.attach(s1);
	win.attach(s2);
	win.attach(s3);
	win.attach(s4);
	win.attach(s5);

	win.attach(slope2);

	win.wait_for_button();


	return 0;
}