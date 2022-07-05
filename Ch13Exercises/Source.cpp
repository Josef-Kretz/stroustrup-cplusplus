#include "Graph.h"
#include "Simple_window.h"

using namespace std;

struct Arcs : Graph_lib::Shape
{
public:
	Arcs(Point p, int width, int height, int arc1, int arc2)
		: w(width), h(height), arcStart(arc1), arcEnd(arc2)
	{
		add(Point{ p.x - width, p.y - height });
	}

	Point center() const
	{
		return { point(0).x + w, point(0).y + h };
	}

	void set_major(int ww)
	{
		set_point(0, Point{ center().x - ww, center().y - h });
		w = ww;
	}
	int major() const { return w; }
	void set_minor(int hh)
	{
		set_point(0, Point{ center().x - w, center().y - hh });
		h = hh;
	}
	int minor() const { return h; }

	void draw_lines() const
	{
		fl_arc(point(0).x, point(0).y, major(), minor(), arcStart, arcEnd);
	}
private:
	int w, h, arcStart, arcEnd;
};

struct Box : Shape
{
public:
	Box(Point p, int width, int height)
		:w(width), h(height)
	{
		origin.x = p.x; origin.y = p.y; //origin used for TL corner
		bCenter.x = int(p.x + w / 10); bCenter.y = int(p.y + h / 1.75); //center point for text

		strLines.add(Point{ p.x, p.y + offset }, Point{ p.x, p.y + h - offset });			//left side
		strLines.add(Point{ p.x + offset, p.y + h }, Point{ p.x + w - offset, p.y + h });	//bottom side
		strLines.add(Point{ p.x + w, p.y + h - offset }, Point{ p.x + w, p.y + offset });	//right side
		strLines.add(Point{ p.x + w - offset, p.y }, Point{ p.x + offset, p.y });			//top side

		/*	//original points for a rectangle
		Point{ p.x, p.y }
		Point{ p.x, p.y + w }
		Point{ p.x + h, p.y + w }
		Point{ p.x + h, p.y }*/

		int radOffset = offset * 2;
		arcList.push_back(new Arcs{ Point{p.x + radOffset, p.y + radOffset}, radOffset, radOffset, 90, 180 }); //top left radius
		arcList.push_back(new Arcs{ Point{p.x + radOffset, p.y + h}, radOffset, radOffset, 180, 270 });			// bottom left radius
		arcList.push_back(new Arcs{ Point{p.x + w, p.y + h}, radOffset, radOffset, 270, 360 });					//bottom right radius
		arcList.push_back(new Arcs{ Point{p.x + w, p.y + radOffset}, radOffset, radOffset, 0, 90 });			//top right radius

		set_color(Color::black);
	}

	void set_label(const string& s) { label.move(bCenter.x, bCenter.y); label.set_label(s); label.set_color(Color::black); }

	Point center() const { return bCenter; }
	Point tl() const { return origin; }
	int width() const { return w; }
	int height() const { return h; }

	void draw_lines() const
	{
		label.draw_lines();
		strLines.draw_lines();
		for (int i = 0; i < arcList.size(); ++i)
			arcList[i].draw_lines();
	}


private:
	int w, h; //width and height of box
	int offset = 3;
	Vector_ref<Arcs> arcList;
	Lines strLines;
	Point bCenter{ 0,0 }; //returns point for text inside box
	Point origin{ 0,0 }; //used to return top left corner
	Text label{ Point{ 0, 0 }, "" };
};

struct BoxCompass
{
public:
	enum CompassRose {
		n = 0, s, e, w, ne, nw, se, sw, center
	};
	BoxCompass(const Box& b)
	{
		p = b.tl();
		h = b.height();
		wid = b.width();
	}



	Point Compass(CompassRose cr)
	{
		switch (cr)
		{
		case CompassRose::n:
			return Point{ p.x + int(wid / 2), p.y };
		case CompassRose::s:
			return Point{ p.x + int(wid / 2), p.y + h };
		case CompassRose::e:
			return Point{ p.x + wid, p.y + int(h / 2) };
		case CompassRose::w:
			return Point{ p.x, p.y + int(h / 2) };
		case CompassRose::ne:
			return Point{ p.x + wid, p.y };
		case CompassRose::nw:
			return p;
		case CompassRose::se:
			return Point{ p.x + wid, p.y + h };
		case CompassRose::sw:
			return Point{ p.x, p.y + h };
		case CompassRose::center:
			return Point{ p.x + int(wid / 2), p.y + int(h / 2) };
		}
	}


private:
	Point p;
	int wid, h;
};

struct Arrow : Shape
{
	enum ArrowDirection 
	//decide if arrow points up, down, left, or right
	{
		up = 1,
		down,
		left,
		right
	}; 

	Arrow(Point p, int size, ArrowDirection ad)
		: origin(p), s(size)
	{
		set_color(Color::black);
		switch (ad)
		{
		case ArrowDirection::up:
			upArrow();
			break;
		case ArrowDirection::down:
			downArrow();
			break;
		case ArrowDirection::left:
			leftArrow();
			break;
		case ArrowDirection::right:
			rightArrow();
			break;
		default:
			throw runtime_error("Incorrect direction! Select ArrowDirection::(up/down/left/right)\n");
		}
	}

	void upArrow();
	void downArrow();
	void leftArrow();
	void rightArrow();

	void draw_lines() const { arr.draw_lines(); }

private:
	int s;
	int tail = s * 2;
	Point origin;
	Lines arr;
};

void Arrow::upArrow()
{
	arr.add(origin, Point{ origin.x, origin.y + tail }); //tail
	arr.add(origin, Point{ origin.x - s, origin.y + s }); //left arrow flange
	arr.add(origin, Point{ origin.x + s, origin.y + s }); //right arrow flange
	
}
void Arrow::downArrow()
{
	arr.add(origin, Point{ origin.x, origin.y - tail });
	arr.add(origin, Point{ origin.x - s, origin.y - s });
	arr.add(origin, Point{ origin.x + s, origin.y - s });
}
void Arrow::leftArrow()
{
	arr.add(origin, Point{ origin.x + tail, origin.y });
	arr.add(origin, Point{ origin.x + s, origin.y - s });
	arr.add(origin, Point{ origin.x + s, origin.y + s });
}
void Arrow::rightArrow()
{
	arr.add(origin, Point{ origin.x - tail, origin.y });
	arr.add(origin, Point{ origin.x - s, origin.y - s });
	arr.add(origin, Point{ origin.x - s, origin.y + s });
}

struct RecCompass
{
public:
	enum CompassRose {
		n = 0, s, e, w, ne, nw, se, sw, center
	};
	RecCompass(const Graph_lib::Rectangle& r)
	{
		p = r.point(0);
		h = r.height();
		wid = r.width();
	}

	

	Point Compass(CompassRose cr)
	{
		switch (cr)
		{
		case CompassRose::n:
			return Point{ p.x + int(wid / 2), p.y };
		case CompassRose::s:
			return Point{ p.x + int(wid / 2), p.y + h };
		case CompassRose::e:
			return Point{ p.x + wid, p.y + int(h / 2) };
		case CompassRose::w:
			return Point{ p.x, p.y + int(h / 2) };
		case CompassRose::ne:
			return Point{ p.x + wid, p.y };
		case CompassRose::nw:
			return p;
		case CompassRose::se:
			return Point{ p.x + wid, p.y + h };
		case CompassRose::sw:
			return Point{ p.x, p.y + h };
		case CompassRose::center:
			return Point{ p.x + int(wid / 2), p.y + int(h / 2) };
		}
	}


private:
	Point p;
	int wid, h;
};

struct CirCompass
{
public:
	enum CompassRose {
		n = 0, s, e, w, ne, nw, se, sw, center
	};

	CirCompass(const Graph_lib::Circle& c)
	{
		di = c.radius() * 2;
		rad = c.radius();
		p = c.center();
	}

	Point Compass(CompassRose cr)
	{
		switch (cr)
		{
		case CompassRose::n:
			return Point{ p.x, p.y - rad };
		case CompassRose::s:
			return Point{ p.x, p.y + rad };
		case CompassRose::e:
			return Point{ p.x + rad, p.y };
		case CompassRose::w:
			return Point{ p.x - rad, p.y };
		case CompassRose::ne:
			return Point{ p.x + rad, p.y - rad };
		case CompassRose::nw:
			return Point{ p.x - rad, p.y - rad };
		case CompassRose::se:
			return Point{ p.x + rad, p.y + rad };
		case CompassRose::sw:
			return Point{ p.x - rad, p.y + rad };
		case CompassRose::center:
			return Point{ p.x, p.y };
		}
	}

private:
	int di, rad;
	Point p;
};

struct ElliCompass
{
public:
	enum CompassRose {
		center = 0, n, s, e, w, ne, nw, se, sw
	};

	ElliCompass(const Graph_lib::Ellipse& el)
	{
		y = el.minor();
		x = el.major();
		p = el.center();
	}

	Point Compass(CompassRose cr)
	{
		switch (cr)
		{
		case CompassRose::n:
			return Point{ p.x, p.y - y };
		case CompassRose::s:
			return Point{ p.x, p.y + y };
		case CompassRose::e:
			return Point{ p.x + x, p.y };
		case CompassRose::w:
			return Point{ p.x - x, p.y };
		case CompassRose::ne:
			return Point{ p.x + x, p.y - y };
		case CompassRose::nw:
			return Point{ p.x - x, p.y - y };
		case CompassRose::se:
			return Point{ p.x + x, p.y + y };
		case CompassRose::sw:
			return Point{ p.x - x, p.y + y };
		case CompassRose::center:
			return Point{ p.x, p.y };
		}
	}

private:
	int x, y;
	Point p;
};

int SizedArrow(const Point& p1, const Point& p2, const Arrow::ArrowDirection& ad)
{
	Arrow::ArrowDirection up = Arrow::ArrowDirection::up;
	Arrow::ArrowDirection down = Arrow::ArrowDirection::down;
	Arrow::ArrowDirection left = Arrow::ArrowDirection::left;
	Arrow::ArrowDirection right = Arrow::ArrowDirection::right;

	int x_size, y_size;
	//arrow size if left/right
	x_size = p1.x - p2.x;
	if (x_size < 0) x_size *= -1;
	//arrow size if up/down
	y_size = p1.y - p2.y;
	if (y_size < 0) y_size *= -1;

	x_size = int(x_size / 2);
	y_size = int(y_size / 2);


	if (ad == up || ad == down) { return y_size; }
	if (ad == left || ad == right) { return x_size; }

	throw runtime_error("Improper input or processing for: SizedArrow()\n");
}


int main()
{
	/*
		//exercise 1 chapter 13
		Point tl{ 100, 100 };
		Simple_window win(tl, 1000, 800, "Testing Arcs");

		 //exercise 1 chapter 13
		Arcs test1{ Point{ 100,100 }, 75, 50, 0, 90 };

		test1.set_color(Color::green);
		win.attach(test1);

		Arcs test2{ Point{ 200,100 }, 75, 50, 90, 99 };
		test2.set_color(Color::magenta);

		Arcs test3{ Point{ 300,500 }, 250, 150, 230, 300 };
		test3.set_color(Color::dark_red);

		win.attach(test2);
		win.attach(test3);*/
		/*	// exercise 2 chapter 13
			Point tl{ 100, 100 };
			Simple_window win(tl, 1000, 800, "Testing Rounded Corners");

			Box testA(Point{ 50,50 }, 100, 200);
			testA.set_color(Color::green);
			win.attach(testA);

			Box testB(Point{ 200, 200 }, 500, 500);
			testB.set_color(Color::blue);
			win.attach(testB);

			Box testC(Point{ 400,400 }, 50, 200);
			testC.set_style(Line_style(Line_style::dashdot, 10));
			testC.set_color(Color::dark_cyan);
			win.attach(testC);

			win.wait_for_button();*/
			/* // exercise 3 chapter 13
			Point tl{ 100, 100 };
			Simple_window win(tl, 1000, 800, "Testing Arrows");

			Arrow upArrow(Point{ 200, 300 }, 50, Arrow::ArrowDirection::up);
			Arrow downArrow(Point{ 200, 200 }, 50, Arrow::ArrowDirection::down);
			Arrow leftArrow(Point{ 250, 250 }, 50, Arrow::ArrowDirection::left);
			Arrow rightArrow(Point{ 150, 250 }, 50, Arrow::ArrowDirection::right);

			win.attach(upArrow);
			win.attach(downArrow);
			win.attach(leftArrow);
			win.attach(rightArrow);*/

			/*	//exercise 4 chapter 13
			Point tl{ 100, 100 };
			Simple_window win(tl, 1000, 800, "Testing Compass Rose System");

			Graph_lib::Rectangle r1(Point{ 150, 150 }, 80, 100);
			r1.set_color(Color::red);
			win.attach(r1);
			RecCompass r1P(r1);

			Vector_ref<Mark> vm;
			for (int i = 0; i < 9; ++i)
			{
				vm.push_back(new Mark(r1P.Compass((RecCompass::CompassRose)i), '0' + i));
				win.attach(vm[i]);
			}


			Graph_lib::Rectangle r2(Point{ 200,150 }, 250, 300);
			r2.set_color(Color::dark_blue);
			win.attach(r2);

			RecCompass r2P(r2);
			Vector_ref<Mark> vm2;
			for (int i = 0; i < 9; ++i)
			{
				vm2.push_back(new Mark(r2P.Compass((RecCompass::CompassRose)i), 'a' + i));
				win.attach(vm2[i]);
			}*/

	Point tl{ 100, 100 };
	Simple_window win(tl, 1000, 800, "Testing Adv Compass System");

	/*	//exercise 5 part 1 chapter 13
	Graph_lib::Circle c1(Point{ 100, 100 }, 75);
	c1.set_color(Color::black);
	win.attach(c1);

	CirCompass cc1(c1);

	Vector_ref<Mark> vmc1;
	for (int i = 0; i < 9; ++i)
	{
		vmc1.push_back(new Mark(cc1.Compass((CirCompass::CompassRose)i), 'a' + i));
		win.attach(vmc1[i]);
	}

	Circle c2(Point{ 500, 300 }, 200);
	c2.set_color(Color::dark_magenta);
	win.attach(c2);

	CirCompass cc2(c2);
	Vector_ref<Mark> vmc2;
	for (int i = 0; i < 9; ++i)
	{
		vmc2.push_back(new Mark(cc2.Compass((CirCompass::CompassRose)i), '1' + i));
		vmc2[i].set_color(Color::dark_green);
		win.attach(vmc2[i]);
	}*/

	/*	//exercise 5 part 2 chapter 13
	Graph_lib::Ellipse e1(Point{ 150, 150 }, 100, 65);
	e1.set_color(Color::blue);
	win.attach(e1);

	ElliCompass ce1(e1);

	Vector_ref<Mark> vmce1;
	for (int i = 0; i < 9; ++i)
	{
		vmce1.push_back(new Mark(ce1.Compass((ElliCompass::CompassRose)i), '1' + i));
		vmce1[i].set_color(Color::dark_blue);
		win.attach(vmce1[i]);
	}

	Graph_lib::Ellipse e2(Point{ 500, 150 }, 75, 125);
	e2.set_color(Color::dark_green);
	win.attach(e2);

	ElliCompass ce2(e2);

	Vector_ref<Mark> vmce2;
	for (int i = 0; i < 9; ++i)
	{
		vmce2.push_back(new Mark(ce2.Compass((ElliCompass::CompassRose)i), '0' + i));
		vmce2[i].set_color(Color::green);
		win.attach(vmce2[i]);
	}*/

	//exercise 6 chapter 13
	Box bb1(Point{ 50, 75 }, 100, 50);
	bb1.set_label("Step 1");
	win.attach(bb1);

	Box bb2(Point{ 250, 75 }, 100, 50);
	bb2.set_label("Step 2");
	win.attach(bb2);

	Box bb3(Point{ 50, 175 }, 100, 50);
	bb3.set_label("Step 3");
	win.attach(bb3);

	Box bb4(Point{ 250, 175 }, 100, 50);
	bb4.set_label("Step 4");
	win.attach(bb4);

	//make object to find points of box
	BoxCompass bb1c(bb1);
	BoxCompass bb2c(bb2);
	BoxCompass bb3c(bb3);
	BoxCompass bb4c(bb4);
	
	Arrow::ArrowDirection tempAD; //temp var to store arrow direction
	int tempSize; //temp var to store arrow size

	tempAD = Arrow::ArrowDirection::right;
	tempSize = SizedArrow(bb1c.Compass(BoxCompass::CompassRose::e), bb2c.Compass(BoxCompass::CompassRose::w), tempAD);
	Arrow step12(bb2c.Compass(BoxCompass::CompassRose::w), tempSize, tempAD);

	tempAD = Arrow::ArrowDirection::down;
	tempSize = SizedArrow(bb1c.Compass(BoxCompass::CompassRose::s), bb3c.Compass(BoxCompass::CompassRose::n), tempAD);
	Arrow step13(bb3c.Compass(BoxCompass::CompassRose::n), tempSize, tempAD);

	tempAD = Arrow::ArrowDirection::up;
	tempSize = SizedArrow(bb4c.Compass(BoxCompass::CompassRose::n), bb2c.Compass(BoxCompass::CompassRose::s), tempAD);
	Arrow step42(bb2c.Compass(BoxCompass::CompassRose::s), tempSize, tempAD);

	tempAD = Arrow::ArrowDirection::left;
	tempSize = SizedArrow(bb4c.Compass(BoxCompass::CompassRose::w), bb3c.Compass(BoxCompass::CompassRose::e), tempAD);
	Arrow step43(bb3c.Compass(BoxCompass::CompassRose::e), tempSize, tempAD);

	win.attach(step12);
	win.attach(step13);
	win.attach(step42);
	win.attach(step43);

	win.wait_for_button();
	

	return 0;
}