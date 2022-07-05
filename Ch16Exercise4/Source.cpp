#include "Simple_window.h"
#include "Graph.h"
#include "Gui.h"

struct Shape_Maker : Window
{
	static enum shape_type{circle =0, square, triangle, hexagon};

	Shape_Maker(Point p, int w, int h, const string& title)
		:Window(p, w, h, title),
		coords(Point{ 100,0 }, 100, 20, "Enter x,y:"),
		size(Point{ 350, 0 }, 50, 20, "Enter shape size:"),
		shapes(Point{ 0, 25 }, 70, 20, Menu::horizontal, "Shapes")
	{
		attach(coords);
		attach(size);

		shapes.attach(new Button(Point{ 0,0 }, 0, 0, "Circle", cb_circle));
		shapes.attach(new Button(Point{ 0,0 }, 0, 0, "Square", cb_square));
		shapes.attach(new Button(Point{ 0,0 }, 0, 0, "Triangle", cb_triangle));
		shapes.attach(new Button(Point{ 0,0 }, 0, 0, "Hexagon", cb_hexagon));
		attach(shapes);

		poly.set_color(Color::black);
		c1.set_color(Color::black);
	}

	static void cb_circle(Address, Address pw) { reference_to<Shape_Maker>(pw).summon(circle); }
	static void cb_square(Address, Address pw) { reference_to<Shape_Maker>(pw).summon(square); }
	static void cb_triangle(Address, Address pw) { reference_to<Shape_Maker>(pw).summon(triangle); }
	static void cb_hexagon(Address, Address pw) { reference_to<Shape_Maker>(pw).summon(hexagon); }

	void summon(const shape_type& t)
	{
		string shape_coords = coords.get_string();
		int num1 = -1;
		int num2 = -1;

		stringstream ss;
		ss << shape_coords;
		while (num2 == -1)
		{
			if (num1 == -1) num1 = box_reader(ss);
			if (num2 == -1) num2 = box_reader(ss);
			if (num2 == -1) return;
		}
		if (num1 < 0 || num2 < 0) return;
		Point shape_center{ num1, num2 };
		
		int shape_size = size.get_int();
		if (shape_size < 1) return;

		switch (t)
		{
		case circle:
			draw_circle(shape_center, shape_size);
			break;
		case square:
			draw_square(shape_center, shape_size);
			break;
		case triangle:
			draw_triangle(shape_center, shape_size);
			break;
		case hexagon:
			draw_hexagon(shape_center, shape_size);
			break;
		}
		

	}

	void draw_circle(Point c_center, int i)
	{
		detach(poly);
		c1.set_radius(i);
		c1.move(0 - c1.center().x, 0 - c1.center().y);
		c1.move(c_center.x, c_center.y);
		attach(c1);
		redraw();
	}
	void draw_square(Point center, int square_size)
	{
		detach(c1);
		poly.clear();
		Point p = center;
		for (int i = 0; i < 360; i += 90)
		{
			double xx = p.x + cos(i * 3.14 / 180) * square_size;
			double yy = p.y + sin(i * 3.14 / 180) * square_size;
			poly.add(Point{ int(xx), int(yy) });
		}
		attach(poly);
		redraw();
	}
	void draw_triangle(Point center, int tri_size)
	{
		detach(c1);
		poly.clear();
		Point p = center;
		for (int i = 0; i < 360; i += 120)
		{
			double xx = p.x + cos(i * 3.14 / 180) * tri_size;
			double yy = p.y + sin(i * 3.14 / 180) * tri_size;
			poly.add(Point{ int(xx), int(yy) });
		}
		attach(poly);
		redraw();
	}

	void draw_hexagon(Point center, int hex_size)
	{
		detach(c1);
		poly.clear();
		Point p = center;
		for (int i = 0; i < 360; i += 60)
		{
			double xx = p.x + cos(i * 3.14 / 180) * hex_size;
			double yy = p.y + sin(i * 3.14 / 180) * hex_size;
			poly.add(Point{ int(xx), int(yy) });
		}
		attach(poly);
		redraw();
	}

	int box_reader(stringstream& s)
	{
		int i;
		while (true)
		{
			s >> i;
			if (s) return i;
			if (s.eof()) return -1;
			if (!(s.good()))
			{
				s.clear();
				char c;
				s >> c;
			}
		}
	}


private:
	Menu shapes;
	In_box coords;
	In_box size;
	Graph_lib::Circle c1{ Point{ 0,0 }, 0 };
	Closed_polyline poly;
};










int main()
{
	try {
		Shape_Maker swin(Point{ 100,100 }, 800, 500, "Shape Maker");
		return gui_main();
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "Unkown error\n";
		return 2;
	}


}