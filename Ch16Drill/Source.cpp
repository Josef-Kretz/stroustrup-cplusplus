//chapter 16 drill
#include "Simple_window.h"
#include "Graph.h"
#include "Gui.h"


struct Lines_window : Window
{
	Lines_window(Point xy, int w, int h, const string& title);

	Open_polyline lines;
	Menu color_menu;
	Menu l_style;

	static void cb_red(Address, Address pw) { reference_to<Lines_window>(pw).red_pressed(); } 	//callback for red button
	static void cb_blue(Address, Address pw) { reference_to<Lines_window>(pw).blue_pressed(); }	//callback for blue button
	static void cb_black(Address, Address pw) { reference_to<Lines_window>(pw).black_pressed(); }	//callback for black button

	static void cb_dash(Address, Address pw) { reference_to<Lines_window>(pw).dash_pressed(); }	//callback for dash style button
	static void cb_dot(Address, Address pw) { reference_to<Lines_window>(pw).dot_pressed(); }	//callback for dot style button
	static void cb_dashdot(Address, Address pw) { reference_to<Lines_window>(pw).dashdot_pressed(); }	//callback dashdot style black button

	//color button actions
	void red_pressed() { change(Color::red); redraw(); }
	void blue_pressed() { change(Color::blue); redraw(); }
	void black_pressed() { change(Color::black); redraw(); }

	void dash_pressed() { alter_linestyle(Line_style::dash); redraw(); }
	void dot_pressed() { alter_linestyle(Line_style::dot); redraw(); }
	void dashdot_pressed() { alter_linestyle(Line_style::dashdot); redraw(); }


	void change(Color c) { lines.set_color(c); }
	void alter_linestyle(Line_style style) { lines.set_style(style); }

private:
	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;


	void next();
	void quit() { hide(); }
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	next_button{ Point{ Window::x_max() - 150, 0 }, 70, 20, "Next Point",
		[](Address, Address pw) {reference_to<Lines_window>(pw).next(); } },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Lines_window>(pw).quit(); } },
	next_x{ Point{ x_max() - 310, 0 }, 50, 20, "Next x:" },
	next_y{ Point {x_max() - 210, 0}, 50, 20, "Next y:" },
	xy_out{ Point{100,0}, 100, 20, "Current (x,y):" },
	color_menu( Point{x_max() - 70, 40}, 70, 20, Menu::vertical, "color" ),
	l_style(Point{ x_max() - 70, 110 }, 70, 20, Menu::vertical, "line style")
{
	//basic line program
	lines.set_color(Color::black);
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	attach(lines);
	//colour selection menu
	color_menu.attach(new Button{ Point{0,0}, 0, 0, "red", cb_red });
	color_menu.attach(new Button{ Point{0,0}, 0, 0, "blue", cb_blue });
	color_menu.attach(new Button{ Point{0,0}, 0, 0, "black", cb_black });
	attach(color_menu);

	//line style selection menu
	l_style.attach(new Button{ Point{0,0}, 0, 0, "Dash", cb_dash });
	l_style.attach(new Button{ Point{0,0}, 0,0,"Dot", cb_dot });
	l_style.attach(new Button{ Point{0,0}, 0, 0, "DashDot", cb_dashdot });
	attach(l_style);
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{ x,y });

	//update current position readout:
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	redraw();
}

int main()
{
	try {
		Lines_window win{ Point{100,100}, 600, 400, "lines" };
		return gui_main();
	}
	catch (exception& e)
	{
		cerr << "Exception: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "Encounted an exception\n";
		return 2;
	}
}