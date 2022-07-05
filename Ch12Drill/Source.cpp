#include "Graph.h"
#include "Simple_window.h"

int main()
{
	using namespace Graph_lib;

	Point tl(150, 150);
	Simple_window win(tl, 1000, 800, "My window");
	win.wait_for_button();

	Axis xa{ Axis::x, Point{20,300}, 280, 10, "x axis" };	//make an axis
		//an Axis is a kind of shape
		//Axis::x means horizontal
		//starting at (20, 300)
		//280 pixels long
		//10 "notches"
		//label the axis "x axis"
	xa.move(200, 200);
	win.attach(xa);
	win.set_label("Canvas #2");
	win.wait_for_button();

	Axis ya{ Axis::y, Point{20,300}, 280, 10, "y axis" };
	ya.set_color(Color::cyan);				//choose a colour
	ya.label.set_color(Color::dark_red);	//chose a text colour
	win.attach(ya);
	win.set_label("Canvas #3");

	xa.set_color(Color::cyan);
	win.attach(xa);
	win.wait_for_button();					//display

	Function sine{ sin, 0, 100, Point{200,200}, 1000, 50, 50 };	//sine curve
				//plot sin() in the range [0:100] with (0,0) at (20,150)
				//using 1000 points; scale x values *50, scale y values *50

	win.attach(sine);
	win.set_label("Canvas #4");
	win.wait_for_button();

	sine.set_color(Color::blue);

	Graph_lib::Polygon poly;		//a polygon; a kind of shape
	poly.add(Point{ 300,200 });		//3 points make a triangle
	poly.add(Point{ 350,100 });
	poly.add(Point{ 400,200 });

	poly.add(Point{ 450,250 });

	poly.set_color(Color::red);
	poly.set_style(Line_style::dash);
	win.attach(poly);
	win.set_label("Canvas #5");
	win.wait_for_button();


	Graph_lib::Rectangle r{ Point{200,200}, 100, 50 };	//top left corner, width, height
	r.set_style(Line_style::dashdot);
	win.attach(r);
	win.set_label("Canvas #6");
	win.wait_for_button();

	Closed_polyline poly_rect;
	poly_rect.add(Point{ 100,50 });
	poly_rect.add(Point{ 200,50 });
	poly_rect.add(Point{ 200,100 });
	poly_rect.add(Point{ 100,100 });

	r.set_color(Color::dark_magenta);
	win.attach(poly_rect);

	poly_rect.add(Point{ 50,75 });

	r.set_fill_color(Color::yellow);		//colour inside of rectangle
	poly.set_style(Line_style(Line_style::dash, 4));	//change triangle to dashed line
	poly_rect.set_style(Line_style(Line_style::dash, 2));	//change poly rectangle to dashed line
	poly_rect.set_fill_color(Color::green);
	win.set_label("Canvas #7");

	r.set_style(Line_style(Line_style::dot, 5));
	win.wait_for_button();

	Text t{ Point{150,150}, "Hello, graphical world!" };
	t.set_color(Color::dark_green);
	win.attach(t);
	win.set_label("Canvas #8");
	win.wait_for_button();

	t.set_font(Font::helvetica_bold_italic);
	t.set_font_size(20);
	win.set_label("Canvas #9");
	win.wait_for_button();

	Image ii{ Point{100,50},"image.jpg" };
	win.attach(ii);
	win.set_label("Canvas #10");
	win.wait_for_button();

	ii.move(100, 200);
	win.set_label("Canvas #11");
	win.wait_for_button();

	Circle c{ Point{100,200},50 };
	Graph_lib::Ellipse e{ Point{100,200},75,25 };
	e.set_color(Color::dark_red);
	Mark m{ Point{100,200}, 'x' };

	ostringstream oss;
	oss << "Screen size: " << x_max() << " * " << y_max()
		<< "; Window size: " << win.x_max() << " * " << win.y_max();
	Text sizes(Point{ 100,20 }, oss.str());

	Image cal{ Point{100, 200}, "image2.jpg" };
	cal.set_mask(Point{ 40,40 }, 200, 150);	//display part of image

	win.attach(c);
	win.attach(m);
	win.attach(e);

	win.attach(sizes);
	win.attach(cal);
	win.set_label("Final Canvas");
	win.wait_for_button();

}