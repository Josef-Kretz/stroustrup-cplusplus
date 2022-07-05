//starting at exercise 7 Chapter 13 rgb colour chart
#include "Simple_window.h"
#include "Graph.h"

struct Regular_hexagon : Closed_polyline
{
public:
	Regular_hexagon(Point p, int radius) 
		:rad(radius)
	{
		set_color(Color::black);
		center.x = p.x; center.y = p.y; //saves center point

		for (int i = 0; i < 360; i += 60)
		{
			double xx = p.x + cos(i * 3.14 / 180) * rad;
			double yy = p.y + sin(i * 3.14 / 180) * rad;
			add(Point{ int(xx), int(yy) });
		}
	}

	Point Center() { return center; }

private:
	Point center{ 0,0 };
	int rad;
};

struct Regular_polygon : Closed_polyline
{
public:
	Regular_polygon(Point p, int sides, int radius)
		: r(radius)
	{
		center.x = p.x; center.y = p.y; //store value of center

		if (sides < 3) throw runtime_error("No legal polygon with less than 3 sides\n");

		int loops = int(360 / sides);

		for (int i = 0; i < 360; i += loops)
		{
			double xx = p.x + cos(i * 3.14 / 180) * r;
			double yy = p.y + sin(i * 3.14 / 180) * r;
			add(Point{ int(xx), int(yy) });
		}
		set_color(Color::black);
	}

	Point Center() const { return center; }

private:
	Point center{ 0,0 };
	int r;
};

int main()
{
	Point tl{ 100,100 };
	Simple_window win(tl, 800, 500, "RGB Colour Chart");

	/*	//exercise 7 chapter 13 RGB Colour Chart
	Vector_ref<Graph_lib::Rectangle> color_matrix;

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			color_matrix.push_back(new Graph_lib::Rectangle{ Point{i * 20, j * 20 }, 20, 20 });
			color_matrix[color_matrix.size() - 1].set_fill_color(Color{ i * 16 + j });
			win.attach(color_matrix[color_matrix.size() - 1]);
		}
	}*/


	/*//exercise 8, 9 chapter 13

	Vector_ref<Regular_hexagon> rhv;

	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			rhv.push_back(new Regular_hexagon(Point{ i * 20, j * 20 }, 10));
			win.attach(rhv[rhv.size()-1]);
		}
	}*/
	/*	//exercise 10 chapter 13
	Vector_ref<Regular_polygon> rpvec;

	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			rpvec.push_back(new Regular_polygon(Point{ i * 30, j * 30 }, 4, 40));
			rpvec[rpvec.size() - 1].set_color(j * 16);
			win.attach(rpvec[rpvec.size() - 1]);
		}
	}*/

		//exercise 11 chapter 13

	win.wait_for_button();

	return 0;
}