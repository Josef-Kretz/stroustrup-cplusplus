#include "Graph.h"
#include "Simple_window.h"

using namespace std;

int main()
{
	Point tl{ 100,100 };

	Simple_window win(tl, 1000, 800, "Drill");

	Vector_ref<Graph_lib::Rectangle> grid;
	
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			grid.push_back(new Graph_lib::Rectangle{ Point{i * 100,j * 100}, 100, 100 });
			if(i == j)
				grid[grid.size() - 1].set_fill_color(Color::red);
			win.attach(grid[grid.size() - 1]);
		}
	}

	string pic = "z.gif";
	

	Image m1{ Point{0, 300}, pic };
	Image m2{ Point{600, 300}, pic };
	Image m3{ Point{300, 500}, pic };

	win.attach(m1);
	win.attach(m2);
	win.attach(m3);

	win.wait_for_button();

	string sp = "sp.jpg";

	for (int i = 0; i < grid.size(); ++i)
	{
		Point p = grid[i].point(0);
		Image bob{ p, sp };
		win.attach(bob);
		win.wait_for_button();
	}


	return 0;
}