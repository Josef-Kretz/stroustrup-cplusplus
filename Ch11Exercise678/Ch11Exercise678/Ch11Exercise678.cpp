#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string DeContract(const string& s);

string WhiteSpace(const string& s)
{
	string s1 = DeContract(s);
	string s2;
	for (char c : s1)
	{
		if (!ispunct(c) || c == '\"' || c == '-')
			s2 += c;
		else
			s2 += ' ';
	}

	string s3;
	for (int i = 0; i < s2.size(); i++)
	{
		bool upper = (i + 1) < s2.size();
		bool lower = (i - 1) > 0;

		if (s2[0] == '-')
			s3 += ' ';
		else if (upper && lower && s2[i] == '-')
		{
			if (isalpha(s2[i - 1]) && isalpha(s2[i + 1]))
				s3 += s2[i];
			else
				s3 += ' ';
		}
		else
			s3 += s2[i];
	}
	return s3;
}

struct Defs {
	string key, value;

	Defs() {}
	Defs(string k, string v) :key(k), value(v) {}
};

string DeContract(const string& s)
{
	string temp;
	for (char c : s)
	{
		temp += tolower(c);
	}
	vector<Defs> contractions{ Defs("I'm", "I am"),Defs("can't", "cannot"), Defs("won't", "will not"), 
		Defs("don't", "do not"), Defs("doesn't", "does not"), Defs("isn't", "is not"),
	Defs("it's","it is"), Defs("here's", "here is") };
	for (Defs d : contractions)
	{
		size_t pos = temp.find(d.key);
		if (pos != temp.npos)
		{
			temp.replace(pos, d.key.size(), d.value);
		}
	}
	
	return temp;
}


int main()
{
	string filename = "inputfile1.txt";
	string endFile = "final.txt";

	ifstream ifs{ filename };
	if (!ifs) throw runtime_error(filename + " unable to be opened\n");

	ofstream ofs{ endFile };
	if (!ofs) throw runtime_error(endFile + " unable to be opened\n");

	vector<string> dictionary;
	while (ifs.good())
	{
		string s;
		getline(ifs, s);
		
		string ss = WhiteSpace(s);
		stringstream sstream{ ss };
		
		for (string word; sstream >> word;)
		{
			bool hasWord = false;
			for (string checkWord : dictionary)
			{
				if (checkWord == word)
				{
					hasWord = true;
					break;
				}
			}
			if (!hasWord) dictionary.push_back(word);
		}
	}

	sort(dictionary.begin(), dictionary.end());
	for (string word : dictionary)
		ofs << word << endl;

	string openNote = "notepad \"" + endFile + "\"";
	system(openNote.c_str());

	return 0;

}