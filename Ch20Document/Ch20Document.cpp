#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

using Line = vector<char>;	//a line is a vector of characters


class Text_iterator { //keep track of line and character position within a line
	list<Line>::iterator ln;
	Line::iterator pos;

public:
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		:ln{ ll }, pos{ pp } {}

	char& operator*() { return *pos; }
	Text_iterator& operator++();

	bool operator==(const Text_iterator& other) const
	{	return ln == other.ln && pos == other.pos;	}

	bool operator!=(const Text_iterator& other) const
	{	return !(*this == other);	}

	Line& line_number() { return* ln; }
	Line::iterator get_pos() { return pos; }
};


Text_iterator& Text_iterator::operator++()
{
	++pos;					//proceed to next character
	if (pos == ln->end()) {
		++ln;				//proceed to next line
		pos = ln->begin();	//bad if ln==ln.end(); so ensure it isn't
	}
	return *this;
}

struct Document {
	list<Line> line;	//a document is a list of lines
	Document() { line.push_back(Line{}); }

	Text_iterator begin() //first character of first line
	{
		return Text_iterator(line.begin(), line.begin()->begin());
	}

	Text_iterator end()
	{
		auto last = line.end();
		--last;	//we know that the document is not empty
		return Text_iterator(last, last->end());
	}
};

template<typename Iterator>
bool match(Iterator first, Iterator last, string s)
{
	string::const_iterator sp = s.begin();
	for (auto p = first; sp != s.end(); ++p)
	{
		if (*p != *sp) return false;
		++sp;
	}
	return true;
}

istream& operator>>(istream& is, Document& d)
{
	for (char ch; is.get(ch);) {
		d.line.back().push_back(ch);	//add the character

		if (ch == '\n') d.line.push_back(Line{});	//add another line
	}
	if (d.line.back().size()) d.line.push_back(Line{});	//add a final empty line
	return is;
}

template<typename Iterator>
Iterator find1(Iterator first, Iterator last, char c)
{
	for (auto a = first; a != last; ++a)
		if (*a == c)
			return a;

	return last;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size() == 0) return last;
	char first_char = s[0];
	while (true)
	{
			auto p = find1(first, last, first_char);
			if (p == last || match(p, last, s)) return p;
			first = ++p;
	}
}

template<typename T>
istream& operator>>(istream& is, vector<T>& v)
{
	T t;
	if (is >> t) v.push_back(t);
	return is;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T>& v)
{
	for (auto p = v.begin(); p != v.end(); ++p)
		os << *p;
	return os;
}
void print(Document& d)
{
	for (auto p : d) cout << p;
	cout << endl;
}

void erase_line(Document& d, int n)
{
	if (n < 0 || d.line.size() - 1 <= n) return;
	auto p = d.line.begin();
	advance(p, n);
	d.line.erase(p);
}

void replace(Document& d, const string& s1, const string& s2)
//find and  replace string s1 in d with s2
{
	Text_iterator dp1 = find_txt(d.begin(), d.end(), s1); //points to first char of found word OR end
	if (dp1 == d.end()) return; //checks if word found

	Line* p = &dp1.line_number();//points to start of Line object
	
	stringstream ss; //copy vector + s2 into ss
	for (auto a = p->begin(); a != dp1.get_pos(); ++a)
		ss << *a;
	for (char c : s2)
		ss << c;
	for (auto a = dp1.get_pos() + s1.size(); a != p->end(); ++a)
		ss << *a;
	
	int newsize = s2.size() - s1.size() + p->size();
	p->resize(newsize);

	char ch;
	for (auto a = p->begin(); ss.get(ch); ++a)
		*a = ch;
}

vector<string>::iterator lex_last(vector<string>& vs)
//exercise 7
{
	if (vs.empty()) throw runtime_error("Empty vector passed to lex_last()");

	vector<string>::iterator last = vs.begin();
	for (vector<string>::iterator s = vs.begin(); s != vs.end(); ++s)
		if (*s > *last)
			last = s;

	return last;
}
unsigned int char_counter(Document& d)
//exercise 8
{
	unsigned int count = 0;

	for (char c : d)
		++count;

	return count;
}

unsigned int word_counter(Document& d, bool only_wspace = false, const string& s = "")
//exercise 9, 10
{
	bool last_char = false; //true if the preceeding char was alphabetic
	unsigned int word_count = 0;
	if(!only_wspace && s.empty())
		for (char c : d)
		{
			if (!last_char && isalpha(c)) ++word_count;
			(isalpha(c)) ? last_char = true : last_char = false;
		}
	else if(only_wspace)
		for (char c : d)
		{
			if (!last_char && !isspace(c)) ++word_count;
			(isspace(c)) ? last_char = false : last_char = true;
		}
	else if(!s.empty())
		for (char c : d)
		{
			size_t find_s = s.find(c);
			if (!last_char && find_s == string::npos) ++word_count;
			(find_s != string::npos) ? last_char = false : last_char = true;
		}

	return word_count;
}

int main()
{
	try {
		Document mydoc;
		stringstream ss;
		ss << "Howdy\nMy name is Captain Awesome\nHow do you do?\nI am well";
		ss >> mydoc;
		print(mydoc);
		replace(mydoc, "Howdy", "hewo");
		replace(mydoc, "Awesome", "OOOOOOOSOME");
		cout << "New version:\n";
		print(mydoc);

		cout << "Number of words (only wspace) in your Document: " << word_counter(mydoc, true) << endl;
		cout << "Number of words in your Document: " << word_counter(mydoc) << endl;
		cout << "Number of words while using custom spacers " << word_counter(mydoc, false, "' '\n") << endl;
		
		cout << "Enter a list of words:\n";
		vector<string> v;
		string s;
		while (getline(cin, s))
			v.push_back(s);

		vector<string>::iterator vi = lex_last(v);
		if (vi != v.end()) cout << "Lexographically last on submitted string was: " << *vi << endl;

	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "ERROR\n";
	}
	return 0;
}