#include "Simple_window.h"
#include "std_lib_facilities.h"
#include "fltk.h"

#include "Graph.h"

int main()
{
	Point tl{ 100,100 }; //topleft corner of our window

	Simple_window win{ tl,600,400,"Canvas" };
	//screen co-ords tl : topleft corner
	//window size 600*400
	//title: Canvas
	win.wait_for_button();
}