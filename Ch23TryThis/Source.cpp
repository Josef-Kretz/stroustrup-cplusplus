#include <iostream>
#include <regex>

#include <string>
#include <vector>
#include <map>

#include <fstream>
#include <sstream>

using namespace std;


class Message 
	//points to the first and last lines of a message
{
	using Line_iter = vector<string>::const_iterator;

	Line_iter first;
	Line_iter last;

public:
	Message(Line_iter p1, Line_iter p2) :first{ p1 }, last{ p2 } {}
	Line_iter begin() const { return first; }
	Line_iter end() const { return last; }

};


struct Mail_file
	//a Mail_file holds all the lines from a file
	//and simplifies access to messages
{
	using Mess_iter = vector<Message>::const_iterator;

	string name;	//filename
	vector<string> lines; //the lines in order
	vector<Message> m; //messagese in order

	Mail_file(const string& n); //read file n into lines

	Mess_iter begin() const { return m.begin(); }
	Mess_iter end() const { return m.end(); }
};

Mail_file::Mail_file(const string& n)
//open file named n
//read the lines from n into lines
//find the messages in the lines and compose them in m
//for simplicity assume every message is ended by a ---- line
{
	ifstream in{ n };	//open the file
	if (!in)
	{
		cerr << "no " << n << " found\n";
		exit(1);		//terminate the program
	}

	regex end{ R"(----+)" };

	for (string s; getline(in, s);)	//build the vector of lines
	{
		smatch matches;
		if (regex_search(s, matches, end))
		{
			size_t st = s.find(matches[0]);
			string s1, s2;

			s1 = s.substr(0, st);
			s2 = s.substr(st + matches[0].length());


			if (s1.size() > 0) lines.push_back(s1);//make sure not to add extra lines
			lines.push_back(matches[0]);
			if (s2.size() > 0) lines.push_back(s2);
		}
		else
			lines.push_back(s);
	}

	auto first = lines.begin();		//build the vector of Messages
	for (auto p = lines.begin(); p != lines.end(); ++p)
	{
		smatch matches;
		if (regex_match(*p, matches, end)) //end of message
		{
			m.push_back(Message(first, p));
			first = p + 1;	//not part of message
		}
	}
}

int is_prefix(const string& s, const string& p)
//is p the first part of s?
{
	int n = p.size();
	if (string(s, 0, n) == p) return n;
	return 0;
}

//find the name of the sender in a Message
//return true if found
//if found, place the sender's name is s:
bool find_from_addr(const Message* m, string& s) {
	for(const auto& x : *m)
		if (int n = is_prefix(x, "From: "))
		{
			s = string(x, n);
			return true;
		}

	return false;
}

//return the subject of the Message, if any, otherwise ""
string find_subject(const Message* m)
{
	for (const auto& x : *m)
		if (int n = is_prefix(x, "Subject: ")) return string(x, n);

	return "";
}

void trythis1()
{
	Mail_file mfile{ "my-mail-file.txt" };	//initialize mfile from a file

	//first gather messages from each sender together in a multimap
	multimap<string, const Message*> sender;

	for (const auto& m : mfile)
	{
		string s;
		if (find_from_addr(&m, s))
			sender.insert(make_pair(s, &m));
	}

	//now iterator through the multimap
	//and extract the subjects of John Doe's messages

	auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
	for (auto p = pp.first; p != pp.second; ++p)
		cout << find_subject(p->second) << endl;
}

void trythis3()
//accept a pattern and a set of lines from input
//check the pattern and search for lines with that pattern
{
	regex pattern;

	string pat;

	cout << "Enter a pattern: ";
	getline(cin, pat);
	try {
		pattern = pat; //this checks pat
		cout << "pattern: " << pat << endl;
	}
	catch (regex_error)
	{
		cout << pat << "is not a valid regular expression\n";
		exit(1);
	}

	cout << "Now enter some lines:\n";
	int lineno = 0;

	for (string line; getline(cin, line);)
	{
		++lineno;
		smatch matches;
		if (regex_search(line, matches, pattern))
		{
			cout << "line " << lineno << ": " << line << endl;
			for (int i = 0; i < matches.size(); ++i)
				cout << "\tmatches[" << i << "]: "
				<< matches[i] << endl;
		}
		else
			cout << "did not match\n";
	}
}

int main()
{

	//trythis3();
	trythis1();

	return 0;
}