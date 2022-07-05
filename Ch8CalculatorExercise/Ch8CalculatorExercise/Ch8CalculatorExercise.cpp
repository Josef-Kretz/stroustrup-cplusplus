
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

/*
* Grammar:
* Statement:
*	Expression
*	Print
*	Quit
*
* Print:
*	;
*
* Quit:
*	q
*
* Expression:
*	Term
*	Expression + Term
*	Expression - Term
*
* Term:
*	Primary
*	Term * Primary
*	Term / Primary
*	Term % Primary
*
* Primary:
*	Number
*	( Expression )
*	-Primary
*	sqrt ( Expression )
*
* Number:
*	floating-point-literal
*/


#include "std_lib_facilities.h"



struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string s) :kind(ch), name(s) { }
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }
	Token_stream(istream&) :full(0), buffer(0) {}

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

void Help()
{
	cout << "Make expressions using numbers and operators.\n"
		<< "Operators: + - * / % sqrt() \n"
		<< "Declare variables using # and declare constants using const\n"
		<< "Type quit to exit the program\n";
}

const char let = '#';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char root = 'r';
const char power = 'p';
const char con = 'c';
const char help = 'h';

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;

	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case print:
	case '%':
	case '=':
	case ',':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget();
	double val;
	cin >> val;
	return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.unget();
			//if (s == "#") return Token(let); //removed this line of code when "let" changed to "#"
			if (s == "quit") return Token(quit);
			if (s == "sqrt") return Token(root);
			if (s == "pow") return Token(power);
			if (s == "const") return Token(con);
			if (s == "help") return Token(help);
			return Token(name, s);
		}
		if (ch == '#') return Token(let);
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

class Symbol_Table {
private:
	string name;
	double value;

public:
	Symbol_Table() {}
	Symbol_Table(string n, double v) :name(n), value(v) {}

	double get(string s);
	void set(string s, double d);
	bool is_declared(string s);

};
struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}


double expression(Token_stream& ts);

//handles brackets, numbers, sqrt(), and negative numbers
double primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':
		return -primary(ts);
	case number:
		return t.value;
	case con:
	{
		t = ts.get();
		if (t.kind != name) error("name of constant expected");
		string tempName = t.name;
		t = ts.get();
		if (t.kind != '=') error("'=' expected");
		tempName = "$" + tempName;
		if (is_declared(tempName)) error("Cannot change value of constant");

		double d = expression(ts);
		names.push_back(Variable(tempName, d));

		return d;

	}
	case name:
	{
		string tempName = t.name;

		t = ts.get();
		if (is_declared("$" + tempName) && t.kind == '=') error("Cannot change value of constant");
		if (is_declared("$" + tempName) && t.kind != '=')
		{
			ts.unget(t);
			return get_value("$" + tempName);
		}
		if (t.kind != '=' && is_declared(tempName))
		{
			ts.unget(t);
			return get_value(tempName);
		}

		if (is_declared(tempName))
		{
			set_value(tempName, expression(ts));
			return get_value(tempName);
		}
		ts.unget(t);
		error("Variable not declared");
	}
	case root:
	{
		double d = primary(ts);
		if (d >= 0) //ensure to take the square root of a real number
			return sqrt(d);
		else
			error("No possible root for supplied expression");
	}
	case power:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ',') error("',' expected");
		double d2 = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("')' expected");

		return pow(d, d2);

	}
	default:
		error("primary expected");
	}
}

//handles *, /, and %
double term(Token_stream& ts)
{
	double left = primary(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary(ts);
			break;
		case '/':
		{	double d = primary(ts);
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%':
		{
			double d = primary(ts);
			if (d <= 0 || left <= 0) error("Unreal number error (%)");
			left = fmod(left, d);
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}


//handles +, - operations
double expression(Token_stream& ts)
{
	double left = term(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term(ts);
			break;
		case '-':
			left -= term(ts);
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

//handles declarations
double declaration(Token_stream& ts)
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression(ts);
	names.push_back(Variable(name, d));
	return d;
}

//handles statements
double statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration(ts);
	default:
		ts.unget(t);
		return expression(ts);
	}
}

//handles errors that were caught
//removes erroneous content from istream
void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";



//handles computation
void calculate(Token_stream& ts)
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == help) Help();
		else if (t.kind == quit) return;
		else
		{
			ts.unget(t);
			cout << result << statement(ts) << endl;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess(ts);
	}
}

//handles errors
int main()
{
	try {
		Token_stream ts;
		names.push_back(Variable("k", 1000));
		calculate(ts);
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >> c && c != ';');
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin >> c && c != ';');
		return 2;
	}
}