#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <numeric>

using namespace std;




template<typename T, typename U>
istream& operator>>(istream& is, map<T, U>& m)
{
	T t;
	U u;
	if (is >> t >> u)
	{
		m.insert(pair<T, U>(t,u));
		return is;
	}
	return is;
}

template<typename T, typename U>
ostream& operator<<(ostream& os, map<T, U>& m)
{
	for (auto a : m)
		os << a.first << " " << a.second << endl;
	return os;
}


template<typename T, typename U>
map<T,U>& user_pairs(map<T,U>& m, int count)
{
	while (count-- > 0)
	{
		cin >> m;
	}
	return m;
}

int main()
{
	string file{ "itemlist.txt" };
	ifstream ifs{ file };
	
	map<string, int> msi;
	while (ifs >> msi);
	cout << msi;

	msi.clear();
	user_pairs(msi, 10);
	cout << "New map:\n" << msi;

	int total = 0;
	for (auto pmsi = msi.begin(); pmsi != msi.end(); ++pmsi)
		total += pmsi->second;
	cout << "Total: " << total << endl;

	map<int, string> mis;
	for (auto pmsi = msi.begin(); pmsi != msi.end(); ++pmsi)
		mis.insert(pair<int, string>(pmsi->second, pmsi->first));

	cout << "Reverse Map:\n" << mis;

	return 0;
}