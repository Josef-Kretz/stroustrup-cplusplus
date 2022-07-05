//chapter 23 exercises 1 - 5
//create a program to parse e-mail files using regular expressions (regex)
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

#include <regex>

using namespace std;

class Message
	//points to first and last lines of a message
{
	using Line_iter = vector<string>::const_iterator;

	Line_iter first;
	Line_iter last;

public:
	Message(Line_iter p1, Line_iter p2) :first(p1), last(p2) {}
	Line_iter begin() const { return first; }
	Line_iter end() const { return last; }
};

struct Mail_file 
	//Mail_file holds all lines from a file
	//and simplifies access to messages
{
	using Mess_iter = vector<Message>::const_iterator;

	string name;	//filename
	vector<string> lines;	//the lines in order
	vector<Message> m;		//messages in order

	Mail_file(const string& n); //read file n into lines

	Mess_iter begin() const { return m.begin(); }
	Mess_iter end() const { return m.end(); }
};

Mail_file::Mail_file(const string& n)
{
	ifstream in{ n };
	if (!in)
		throw runtime_error(n + " file not found");
	name = n;

	regex marker{ R"(([^----]*)(----+)([^----]*))" };
	regex exact_mark{ R"(----+)" };

	for (string s;getline(in, s);)
	{
		smatch matches;
		if (regex_match(s, matches, marker))
		{
			if (matches[1].length() > 0) lines.push_back(matches[1]);
			lines.push_back(matches[2]);	//checked matches[0] success at if()
			if (matches[3].length() > 0) lines.push_back(matches[3]);
		}
		else
			lines.push_back(s);
	}

	auto p = lines.begin();
	for (auto pp = p; pp != lines.end(); ++pp)
	{
		smatch matches2;
		if (regex_match(*pp, matches2, exact_mark) && pp != p)
		{
			m.push_back(Message(p, pp));
			p = pp + 1;
		}

	}
}

bool find_from_addr(const Message* m, string& s)
//find the name of the sender in a Message
//return true if found
//if found place sender's name in s:
{
	regex adr_field{ R"(\s*(from)\s*:\s*(.*))", std::regex_constants::icase };

	for(const string &p : *m)
	{
		smatch matches;
		if (regex_match(p, matches, adr_field))
		{
			s = matches[2];
			return true;
		}
	}

	return false;
}

bool find_subject(const Message* m, string& s)
//find the subject of the message
//return true if found
//if found, place subject in string
{
	regex subj_field{ R"(\s*(subject)\s*:\s*(.*)$)", std::regex_constants::icase };

	for (auto p : *m)
	{
		smatch matches;
		if (regex_match(p, matches, subj_field))
		{
			s = matches[2];
			return true;
		}
	}

	return false;
}

void print_message(const Message* m, ostream& os = cout)
//prints entire message from m.begin() to m.end()
{
	for (auto s : *m)
	{
		os << s << endl;
	}
}

void user_search(const unordered_multimap<string, const Message*>& subs)
//searches for s in subjects, if found it prints the entire message
{
	try {
		cout << "Enter a subject to search: ";
		string search;
		getline(cin, search);

		regex look{ search, std::regex_constants::icase };

		for (const auto& s : subs)
		{
			smatch matches;
			if (regex_search(s.first, matches, look))
				print_message(s.second);
		}
	}
	catch (regex_error)
	{
		cerr << "Unable to handle user input\n";
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
}


void ex4(Mail_file& mf)
//search mail for sender, print subjects
//get sender from user input
{
	//every e-mail starts with
	//Delivered-To:
	//no invariant for e-mail end

	regex start{ R"((Delivered-To:)\s*(.*)$)" };

	vector<Message> &mess= mf.m;
	mess.clear();
	vector<string>& mfL = mf.lines;

	auto spb = mfL.begin();
	for (auto sp = mfL.begin(); sp != mfL.end(); ++sp)
	{
		smatch matches;
		if (regex_match(*sp, matches, start) && sp != spb)
		{
			mess.push_back(Message(spb, sp-1));
			spb = sp;
		}
	}

	unordered_multimap<string, const Message*> sender;
	for (auto& m : mf)
	{
		string s;
		if (find_from_addr(&m, s))
			sender.insert(make_pair(s, &m));
	}

	set<string> send_list;
	for (auto mp = sender.begin(); mp != sender.end(); ++mp)
		send_list.insert(mp->first);

	cout << "Select from the list of Senders:\n";
	for (auto s : send_list)
		cout << s << endl;

	string user_pick;
	getline(cin, user_pick);

	try { 
	regex upick{ user_pick, std::regex_constants::icase }; 

	for (string s : send_list)
	{
		smatch matches;
		if (regex_search(s, matches, upick))
		{
			user_pick = s;
			break;
		}
	}

	cout << "Results for \"" << user_pick << "\":\n";
	auto up = sender.equal_range(user_pick);
	string subline;
	for (auto upp = up.first; upp != up.second; ++upp)
		if (find_subject(upp->second, subline))
			cout << subline << endl;

	}
	catch (regex_error)
	{
		cerr << "Bad Token Submitted\n";
	}
}

int main()
{
	string filename = "alt-mail.txt";
	Mail_file mfile(filename);	//initialize mfile from a file
	/*
	//first gather messages from each sender together in a multimap
	unordered_multimap<string, const Message*> sender;
	
	for (const auto& m : mfile)
	{
		string s;
		if (find_from_addr(&m, s))
			sender.insert(make_pair(s, &m));
	}

	//now iterate through multimap
	//and extract subjects of John Doe's messages
	auto pp = sender.equal_range("John Doe <jdoe@machine.example>");

	string subject;
	for (auto p = pp.first; p != pp.second; ++p)
		if (find_subject(p->second, subject))
			cout << subject << endl;

	//multimap containing all subjects
	unordered_multimap<string, const Message*> subjects;
	for (const auto& m : mfile)
	{
		string s;
		if (find_subject(&m, s))
			subjects.insert(make_pair(s, &m));
	}

	//user_search(subjects);*/

	//exercise 4, alt email source
	ex4(mfile);

	return 0;
}