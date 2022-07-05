#include "Gui.h"
#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities.h"


struct Image_button : Window
{
	Image_button(Point p, int w, int h, const string& image_filename)
		:Window(p, w, h, "Click image to move"),
		iButt(Point{ 50, 50 }, 141, 200, " ",
			[](Address, Address pw) { reference_to<Image_button>(pw).pic(); }),
		saved_image(Point{ 50,50 }, image_filename)
	{
		saved_image.set_mask(Point{ 0,0 }, 141, 200);
		attach(iButt);
		attach(saved_image);
	}

	void pic()
	{
		int random_x = randint(0, x_max() - 200);
		int random_y = randint(0, y_max() - 200);

		const Point& p = iButt.loc;

		int xx = random_x - p.x;
		int yy = random_y - p.y;

		iButt.move(xx, yy);
		saved_image.move(xx, yy);


	}

private:
	Button iButt;
	Image saved_image;
};



int main()
{
	try {
		Image_button ib(Point{ 100, 100 }, 800, 500, "image.jpg");
		return gui_main();
	}
	catch (exception& e)
	{
		cerr << "Exception: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "Unknown error or exception\n";
		return 3;
	}
}