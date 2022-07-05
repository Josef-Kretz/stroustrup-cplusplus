#include "Gui.h"
#include "Simple_window.h"
#include "Graph.h"


struct My_window : Window
{
	My_window(Point p, int w, int h, const string& title)
		: Window(p, w, h, title),
		next_button(Point{x_max() - 70,0 }, 70, 20, "Next", cb_next),
		quit_button(Point{ x_max() - 70, 20 }, 70, 20, "Quit", cb_quit)
	{
		attach(next_button);
		attach(quit_button);
	}

	static void cb_next(Address, Address pw) { reference_to<My_window>(pw).next(); }	//callback for next button
	static void cb_quit(Address, Address pw) { reference_to<My_window>(pw).quit(); }	//callbackk for quit button

	void next();
	void quit() { hide(); }

private:
	Button next_button;
	Button quit_button;
	bool next_button_pressed = false;
};

void My_window::next()
{
	while (!next_button_pressed) Fl::wait();
	next_button_pressed = false;
	Fl::redraw();
}

int test = 0;

struct Square_window : My_window
{
	Square_window(Point p, int w, int h, const string& title)
		:My_window(p, w, h, title)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				int num = i * 4 + j;
				buttons.push_back(new Button(Point{ 50 + 50 * j, 50 + 50 * i }, 50, 50, to_string(i * 4 + j),
					test(num) ));
				attach(buttons[buttons.size() - 1]);
				}
			}
	}

	Callback test(int i)
	{
		switch (i)
		{
		case 0:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(0); };
		case 1:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(1); };
		case 2:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(2); };
		case 3:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(3); };
		case 4:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(4); };
		case 5:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(5); };
		case 6:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(6); };
		case 7:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(7); };
		case 8:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(8); };
		case 9:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(9); };
		case 10:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(10); };
		case 11:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(11); };
		case 12:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(12); };
		case 13:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(13); };
		case 14:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(14); };
		case 15:
			return [](Address, Address pw) {reference_to<Square_window>(pw).hit(15); };
		}
	}

	void hit(int i)
	{ 
		for (int i = 0; i < 16; ++i)
		{
			buttons[i].show();
		}
		buttons[i].hide();
		redraw();
	}

private:
	Vector_ref<Button> buttons;

};




int main()
{

	try {
		Square_window swin(Point{ 100,100 }, 800, 500, "Square Window");
		return gui_main();
	}
	catch (exception& e)
	{
		cerr << "Exception: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "Unkown exception\n";
	}

}