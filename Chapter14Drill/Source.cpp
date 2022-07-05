//chapter 14 drill: inheritance, overriding, object oriented programming

#include <iostream>
#include <string>

class B1
{
public:
	void f() { std::cout << "B1::f() "; }
	virtual void vf() { std::cout << "B1::vf() "; }
	
	virtual void pvf() = 0;
};

class D1 : public B1
{
public:
	void vf() { std::cout << "D1::vf() "; }
	void f() { std::cout << "D1::f() "; }
};

class D2 : public D1
{
public:
	void pvf() { std::cout << "D2::pvf() "; }
};

class B2
{
public:
	virtual void pvf() = 0;
};

class D21 : public B2
{
public:
	D21(std::string ss) : s(ss) {}
	void pvf() { std::cout << s << std::endl; }

private:
	std::string s;
};

class D22 : public B2
{
public:
	D22(int ii) : i(ii) {}
	void pvf() { std::cout << i << std::endl; }

private:
	int i;
};

void f(B2& b)
{
	b.pvf();
}

int main()
{
	/*B1 b;
	b.vf();
	b.f();

	std::cout << std::endl;

	D1 d;
	d.vf();
	d.f();

	std::cout << std::endl;

	B1& bt = d;
	bt.vf();
	bt.f();
	
	std::cout << std::endl;

	D2 dd;
	dd.pvf();
	dd.vf();
	dd.f();

	std::cout << std::endl;*/

	D21 testD21("Hello World!");
	D22 testD22(46);

	f(testD21);
	f(testD22);

	return 0;
}