#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> IFVector()
{
	
	ifstream ifs{ "mynums.txt" };
	
	if (!ifs) throw runtime_error("Can't open file");
	
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	
	vector<int> toReturn;
	
	for (int num; ifs >> num;)
		toReturn.push_back(num);

	if (ifs.bad()) throw runtime_error("Bad error IFSVector");

	return toReturn;
}

long int total(vector<int> v)
{
	if (v.size() == 0) throw runtime_error("Empty vector passed to total");

	int sum = 0;
	for (int i : v)
		sum += i;

	return sum;
}

int main()
{
	try {
		cout << total(IFVector()) << endl;
	}
	catch (runtime_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	return 0;
}