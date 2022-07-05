#include "Simple_window.h"
#include "Graph.h"

struct Smiley : Circle
{
public:
	Smiley(Point pCircle, int rCircle)
		:Circle{ pCircle, rCircle }, p(Circle::center()), sRad(rCircle)
	{
		set_color(Color::black);
		left.x = int(p.x - (sRad / 2) * (cos(45)));
		left.y = int(p.y - (sRad / 2) * (sin(45)));

		right.x = int(p.x + (sRad / 2) * (cos(45)));
		right.y = int(p.y - (sRad / 2) * (sin(45)));

		mouth.x = int(p.x - sRad / 4);
		mouth.y = int(p.y + sRad / 4);

	}

	void draw_lines() const
	{
		Circle::draw_lines();

		Circle leftEye(left, int(sRad / 8));
		leftEye.draw_lines();

		Circle rightEye(right, int(sRad / 8));
		rightEye.draw_lines();

		fl_arc(mouth.x, mouth.y, sRad/2, sRad/2, 180, 360);
	}

private:
	int sRad;
	Point p, left, right, mouth;
};

struct Frowny : Circle
{
public:
	Frowny(Point pCircle, int rCircle)
		:Circle{ pCircle, rCircle }, p(Circle::center()), sRad(rCircle)
	{
		set_color(Color::black);
		left.x = int(p.x - (sRad / 2) * (cos(45)));
		left.y = int(p.y - (sRad / 2) * (sin(45)));

		right.x = int(p.x + (sRad / 2) * (cos(45)));
		right.y = int(p.y - (sRad / 2) * (sin(45)));

		mouth.x = int(p.x - sRad / 4);
		mouth.y = int(p.y + sRad / 4);

	}

	void draw_lines() const
	{
		Circle::draw_lines();

		Circle leftEye(left, int(sRad / 8));
		leftEye.draw_lines();

		Circle rightEye(right, int(sRad / 8));
		rightEye.draw_lines();

		fl_arc(mouth.x, mouth.y, sRad / 2, sRad / 2, 0, 180);
	}

private:
	int sRad;
	Point p, left, right, mouth;
};

struct S_Hat : Smiley
{
	S_Hat(Point p, int radius)
		:Smiley(p, radius), pCircle(p), r(radius)
	{
		set_color(Color::black);
	}

	void draw_lines() const
	{
		Smiley::draw_lines();

		Graph_lib::Rectangle hatBrim(Point{ pCircle.x - r, pCircle.y - r - r / 10 }, Point{ pCircle.x + r, pCircle.y - r });
		hatBrim.set_fill_color(Color::black);
		hatBrim.draw_lines();

		Graph_lib::Rectangle hat(Point{ int(pCircle.x - r / 2), int(pCircle.y - r * 2) }, Point{ int(pCircle.x + r / 2), int(pCircle.y - r) });
		hat.set_fill_color(Color::black);
		hat.draw_lines();

	}

private:
	Point pCircle;
	int r;
};

struct F_Hat : Frowny
{
	F_Hat(Point p, int radius)
		:Frowny(p, radius), pCircle(p), r(radius)
	{
		set_color(Color::black);
	}

	void draw_lines() const
	{
		Frowny::draw_lines();

		Graph_lib::Rectangle hatBrim(Point{ pCircle.x - r, pCircle.y - r - r / 10 }, Point{ pCircle.x + r, pCircle.y - r });
		hatBrim.set_fill_color(Color::black);
		hatBrim.draw_lines();

		Graph_lib::Rectangle hat(Point{ int(pCircle.x - r / 2), int(pCircle.y - r * 2) }, Point{ int(pCircle.x + r / 2), int(pCircle.y - r) });
		hat.set_fill_color(Color::black);
		hat.draw_lines();

	}

private:
	Point pCircle;
	int r;
};

struct wild
	//created to demonstrate inability to create an object of an abstract class
{
	virtual void f() = 0;
};

class Striped_Rectangle : public Graph_lib::Rectangle
{
public:
	Striped_Rectangle(Point p, int w, int h)
		: Graph_lib::Rectangle(p, w, h), width(w), height(h)
	{
		for (int i = 0; i < h; i += 2)
		{
			Point a{ p.x, p.y + i };
			Point b{ p.x + w, p.y + i };
			hStripes.add(a, b);
		}
		set_color(Color::black);
	}

	void draw_lines() const
	{
		hStripes.draw_lines();
		Graph_lib::Rectangle::draw_lines();
	}

private:
	int width, height;
	Lines hStripes;
};

class Striped_Circle : public Circle
{
public:
	Striped_Circle(Point p, int r)
		: Circle(p, r), radius(r)
	{
		set_color(Color::black);

		int check = int(360 / (radius*0.5));

		for (int i = 90; i < 270; i += check)
		{
			int ri = i + 180;
			double xx1 = p.x + cos(i * 3.14 / 180) * radius;
			double yy1 = p.y + sin(i * 3.14 / 180) * radius;

			double xx2 = p.x + cos(ri * 3.14 / 180) * radius;
			double yy2 = yy1;

			hStripes.add(Point{ int(xx1), int(yy1) }, Point{ int(xx2), int(yy2) });
		}
		
	}

	void draw_lines() const
	{
		Circle::draw_lines();
		hStripes.draw_lines();
	}

private:
	int radius;
	Lines hStripes;
};

struct Immobile_Circle : Circle
{
	Immobile_Circle(Point p, int rad)
		: Circle(p, rad) {}

	void move(int x, int y) { return; }
};

int main()
{
	/*Simple_window win(Point{ 100,100 }, 800, 500, "Chapter 14 Exercise 1");

	S_Hat s1(Point{ 100, 100 }, 75);
	win.attach(s1);

	S_Hat s2(Point{ 200, 200 }, 25);
	win.attach(s2);

	F_Hat f1(Point{ 400, 200 }, 150);
	win.attach(f1);

	F_Hat f2(Point{ 550, 400 }, 90);
	win.attach(f2);

	//example of trying to create an object on an abstract class
	//chapter 14 exercise 3
	//wild w;

	win.wait_for_button();

	Simple_window win2(Point{ 100,100 }, 800, 500, "Chapter 14 Exercise 4");

	Immobile_Circle ic1(Point{ 100, 100 }, 50);
	Circle testCircle(Point{ 100, 100 }, 25);

	win2.attach(ic1);
	win2.attach(testCircle);

	win2.wait_for_button();

	ic1.move(300, 0);
	testCircle.move(300, 0);

	win2.wait_for_button();*/

	//chapter 14 exercise 5, 6
	Simple_window win3(Point{ 100,100 }, 800, 500, "Chapter 14 Exercise 5, 6");

	/*Striped_Rectangle sr1(Point{ 50,50 }, 100, 250);
	win3.attach(sr1);

	Striped_Rectangle sr2(Point{ 350, 50 }, 75, 400);
	win3.attach(sr2);


	win3.wait_for_button();*/

	Striped_Circle sc1(Point{ 50, 50 }, 50);
	win3.attach(sc1);

	Striped_Circle sc2(Point{ 150, 150 }, 100);
	win3.attach(sc2);

	win3.wait_for_button();

	return 0;
}