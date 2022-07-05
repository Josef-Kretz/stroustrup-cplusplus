#include "Simple_window.h"
#include "Graph.h"

int main()
{
	using namespace Graph_lib;

	Point tl{ 100,100 };
	Simple_window win(tl, x_max()*0.75, y_max()*0.66, "");

	Graph_lib::Rectangle r(Point{ 50,50 }, Point{ 150,80 });
	r.set_color(Color::blue);

	Graph_lib::Polygon rpoly;
	rpoly.add(Point{ 250, 200 });
	rpoly.add(Point{ 350, 200 });
	rpoly.add(Point{ 350, 350 });
	rpoly.add(Point{ 250, 350 });

	rpoly.set_color(Color::red);

	win.attach(r);
	win.attach(rpoly);
	//win.wait_for_button();

	Text t{ Point{75, 75}, "Howdy!" };
	t.set_color(Color::blue);

	Text t1{ Point{300, 300}, "J" };
	Text t2{ Point{360, 300 }, "K" };
	t1.set_color(Color::green);
	t2.set_color(Color::dark_green);
	t1.set_font_size(150);
	t2.set_font_size(150);
	win.attach(t);
	win.attach(t1);
	win.attach(t2);
	//win.wait_for_button();

	Graph_lib::Rectangle s1{ Point{100, 100}, Point{150, 150} };
	Graph_lib::Rectangle s2{ Point{150, 150}, Point{200, 200} };
	Graph_lib::Rectangle s3{ Point{200, 200}, Point{250, 250} };

	Graph_lib::Rectangle s4{ Point{150, 100}, Point{200, 150} };
	Graph_lib::Rectangle s5{ Point{100, 150}, Point{150, 200} };
	Graph_lib::Rectangle s6{ Point{200, 150}, Point{250, 200} };
	Graph_lib::Rectangle s7{ Point{150, 200}, Point{200, 250} };

	Graph_lib::Rectangle s8{ Point{100, 200}, Point{150, 250} };
	Graph_lib::Rectangle s9{ Point{200, 100}, Point{250, 150} };

	s1.set_fill_color(Color::red);
	s2.set_fill_color(Color::red);
	s3.set_fill_color(Color::red);

	s4.set_fill_color(Color::white);
	s5.set_fill_color(Color::white);
	s6.set_fill_color(Color::white);
	s7.set_fill_color(Color::white);

	s8.set_fill_color(Color::red);
	s9.set_fill_color(Color::red);

	win.attach(s1);
	win.attach(s2);
	win.attach(s3);
	win.attach(s4);
	win.attach(s5);
	win.attach(s6);
	win.attach(s7);
	win.attach(s8);
	win.attach(s9);

	//win.wait_for_button();

	int y = int(y_max() * 0.66);
	int x = int(x_max() * 0.75);

	Graph_lib::Rectangle bigR{ Point{0,0}, Point{ x, y} };
	bigR.set_color(Color::red);
	bigR.set_style(Line_style(Line_style::solid, 50));

	win.attach(bigR);

	//win.wait_for_button();

	//uncomment to demonstrate window size too big
	//Simple_window test(tl, y_max() * 2, x_max() * 2, "Big Crazy");
	//test.wait_for_button();

	Simple_window house(tl, x, y, "Portrait of a House");
	house.wait_for_button();

	Graph_lib::Rectangle base{ Point{50, 200}, Point{250, 400} };

	Graph_lib::Polygon roof;
	roof.add(Point{ 50, 200 });
	roof.add(Point{ 250, 200 });
	roof.add(Point{ 150, 25 });

	Graph_lib::Rectangle window1{ Point{75, 100}, Point{100, 125} };
	window1.set_fill_color(Color::white);
	
	house.attach(roof);
	house.attach(base);
	house.attach(window1);

	house.wait_for_button();
}