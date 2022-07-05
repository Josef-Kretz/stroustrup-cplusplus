#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> FileReader(ifstream& ifs)
//reads lines of text file into a vector
//pass opened file to function
{
	vector<string> toReturn;

	for (string s; ifs >> s;)
		toReturn.push_back(s);

	ifs.close(); //closes the ifstream before returning vector

	return toReturn;
}

void FileOut(ofstream& ofs, vector<string> vs)
//prints vector string into file
{
	for (string s : vs)
		ofs << s << " ";

	ofs.close();
}

int main()
{
	string file1 = "first.txt";
	string file2 = "second.txt";
	string endFile = "final.txt";

	ifstream ifs1{ file1 };
	if (!ifs1) throw runtime_error(file1 + " unable to be opened\n");

	ifstream ifs2{ file2 };
	if (!ifs2) throw runtime_error(file2 + " unable to be opened\n");

	ofstream ofs{ endFile };
	if (!ofs) throw runtime_error(endFile + " unable to open\n");

	vector<string> first = FileReader(ifs1);

	vector<string> second = FileReader(ifs2);

	vector<string> final;

	for (string s : first)
		final.push_back(s);

	for (string s : second)
		final.push_back(s);

	sort(final.begin(), final.end());

	FileOut(ofs, final);

	string openNotepad = "notepad \"" + endFile + "\"";
	system(openNotepad.c_str());

	return 0;
}