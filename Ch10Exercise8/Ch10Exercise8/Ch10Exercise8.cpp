#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void CopyFile(ifstream& ifs, ofstream& ofs)
{
	for (string s; getline(ifs, s);)
		ofs << s << endl;
}

int main()
{
	string file1 = "first.txt";
	string file2 = "second.txt";

	string endFile = "final.txt";

	ifstream ifs1{ file1 };
	if (!ifs1) throw runtime_error("Cannot access file " + file1);

	ifstream ifs2{ file2 };
	if (!ifs2) throw runtime_error("Cannot access file " + file2);

	ofstream ofs{ endFile };
	if (!ofs) throw runtime_error("Cannot access file " + endFile);

	for (string s; getline(ifs1, s);)
	{
		ofs << s << endl;
	}

	ofs << endl; //add a space for aesthetic

	for (string s; getline(ifs2, s);)
	{
		ofs << s << endl;
	}
	
	string runNotepad = "notepad \"" + endFile + "\""; //opens file in notepad
	system(runNotepad.c_str());

	return 0;

}