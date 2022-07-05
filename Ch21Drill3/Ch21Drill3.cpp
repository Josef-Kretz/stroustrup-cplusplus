#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>

using namespace std;


vector<double>& user_doubles(const string& filename, vector<double>& v)
{
	ifstream ifs{ filename };
	if (!ifs) throw runtime_error("Could not open file: " + filename);

	double d;
	while (ifs >> d)
		v.push_back(d);

	return v;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> v)
{
	for (T t : v)
		os << t << endl;
	return os;
}


int main()
{
	vector<double> user_data;
	user_doubles("itemlist.txt", user_data);
	cout << user_data;

	vector<int> int_user_data;
	int_user_data.reserve(user_data.size());
	for (double d : user_data)
		int_user_data.push_back(int(d));

	cout << "Int-ized user data:\n" << int_user_data;
	cout << "Paired user data values:\n";
	for (int i = 0; i < user_data.size(); ++i)
		cout << "(" << user_data[i] << "," << int_user_data[i] << ")" << endl;

	double dtotal_data = accumulate(user_data.begin(), user_data.end(), double(0));
	int itotal_data = accumulate(int_user_data.begin(), int_user_data.end(), int(0));

	cout << "Total of user_data: " << dtotal_data << endl;
	cout << "Difference between floating and integer data sums: " << dtotal_data - itotal_data << endl;

	reverse(user_data.begin(), user_data.end());
	cout << "REVERSED DATA:\n" << user_data;
	
	double d_mean = dtotal_data / user_data.size();
	cout << "Mean user data: " << d_mean << endl;

	vector<double> vd2(user_data.size());
	copy_if(user_data.begin(), user_data.end(), vd2.begin(),
		[d_mean](double d) ->bool { return d < d_mean; });
	cout << "Values less than " << d_mean << endl
		<< vd2;

	sort(user_data.begin(), user_data.end());
	cout << "Sorted user data:\n" << user_data;
	return 0;
}