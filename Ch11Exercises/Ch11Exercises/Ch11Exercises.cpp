#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void LowerCaseFile()
{
	string filename = "inputfile1.txt";
	ifstream ifs{ filename };
	if (!ifs) throw runtime_error(filename + " cannot be opened\n");

	string endFile = "final.txt";
	ofstream ofs{ endFile };
	if(!ofs) throw runtime_error(endFile + " cannot be opened\n");

	vector<string> normalStrings;

	while (ifs.good())
	{
		string s;
		getline(ifs, s);
		normalStrings.push_back(s);
	}

	vector<string> lowercase;
	for (string s : normalStrings)
	{
		string ss;
		for (char c : s)
		{
			ss += tolower(c);
		}
		lowercase.push_back(ss);
	}

	for (string s : lowercase)
		ofs << s << endl;

	string openNotepad = "notepad \"" + endFile + "\"";
	system(openNotepad.c_str());
}

void WordFind()
{

	cout << "Please provide a word to find:\n";
	string word;
	cin >> word;

	cout << "Please provide a file to search:\n";
	string filename;
	cin >> filename;
	ifstream ifs{ filename };
	if (!ifs) throw runtime_error(filename + " cannot be opened\n");

	vector<string> lines;
	while (ifs.good())
	{
		string s;
		getline(ifs, s);
		lines.push_back(s);
	}

	vector<string> cleanLine;
	for (string s : lines)
	{
		string ss;
		for (char c : s)
		{
			ss += tolower(c);
		}
		cleanLine.push_back(ss);
	}

	vector<string> foundLine;
	for (int i = 0; i < cleanLine.size(); ++i)
	{
		string s = cleanLine[i];
		string num = to_string(i+1);

		size_t wfind = s.find(word);

		if (wfind != string::npos)
			foundLine.push_back(num + " " + s);
	}

	if (foundLine.empty())
	{
		cout << "No matching words found\n";
		return;
	}
	for (string s : foundLine)
		cout << s << endl;

}

void Disemvowels()
{
	cout << "Enter a file name to removes its vowels:\n";
	string filename;
	cin >> filename;

	ifstream ifs{ filename };
	if (!ifs) throw runtime_error(filename + " cannot be opened\n");

	string endFile = "final.txt";
	ofstream ofs{ endFile };
	if (!ofs) throw runtime_error(endFile + " cannot be opened\n");


	vector<string> readLines;
	while (ifs.good())
	{
		string s;
		getline(ifs, s);
		readLines.push_back(s);
	}

	vector<string> newLines;
	for (string s : readLines)
	{
		string ss;
		for (char c : s)
		{
			switch (c)
			{
			case'a':case'e':case'i':case'o':case'u':
			case'A':case'E':case'I':case'O':case'U':
				break;
			default:
				ss += c;
			}
		}
		newLines.push_back(ss);
	}

	for (string s : newLines)
		ofs << s << endl;

	string openNotepad = "notepad \"" + endFile + "\"";
	system(openNotepad.c_str());
}

string Classified(char c)
{
	string s;

	if (isspace(c))
		s += " is a space.";
	if (isalpha(c))
		s += " is a letter,";
	if (isdigit(c))
		s += " is a digit,";
	if (isxdigit(c))
		s += " is a hex digit,";
	if (isupper(c))
		s += " is an uppercase letter,";
	if (islower(c))
		s += " is a lowercase letter,";
	if (isalnum(c))
		s += " is alphanumeric,";
	if (iscntrl(c))
		s += " is a control character,";
	if (ispunct(c))
		s += " is a punctuation character,";
	if (isprint(c))
		s += " is a printable character,";
	if (isgraph(c))
		s += " is not a whitespace character.";

	return s;
}

void CharClassifier()
{
	string filename = "inputfile1.txt";
	ifstream ifs{ filename };
	if (!ifs) throw runtime_error(filename + " cannot be opened\n");

	string endFile = "final.txt";
	ofstream ofs{ endFile };
	if (!ofs) throw runtime_error(endFile + " cannot be opened\n");

	vector<string> inputString;
	while (ifs.good())
	{
		string s;
		getline(ifs, s);
		inputString.push_back(s);
	}

	vector<char> parsedStrings;
	for (string s : inputString)
		for (char c : s)
			parsedStrings.push_back(c);

	for (char c : parsedStrings)
	{
		string classifiers = Classified(c);
		ofs << c << classifiers << endl;
	}

	string openNotepad = "notepad \"" + endFile + "\"";
	system(openNotepad.c_str());
}

int main()
{
	try {
		//LowerCaseFile();
		//WordFind();
		//Disemvowels();
		CharClassifier();
	}
	catch (runtime_error& e)
	{
		cout << "Error " << e.what() << endl;
	}
	return 0;
}