#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


struct Item
{
	string name;
	int iid;
	double value;

	Item() { name = ""; iid = -1; value = -1; }
	Item(string s, int i, double v)
		:name(s), iid(i), value(v) {}

	bool operator==(const string& s) const
	{
		return name == s;
	}

	bool operator==(const int& id) const
	{
		return iid == id;
	}
};

struct Item_namesort {
	bool operator()(const Item& i1, const Item& i2) const
	{
		return i1.name < i2.name;
	}
};
struct Item_iidsort {
	bool operator()(const Item& i1, const Item& i2) const
	{
		return i1.iid < i2.iid;
	}
};
struct Item_valuesort {
	bool operator()(const Item& i1, const Item& i2) const
	{
		return i1.value < i2.value;
	}
};

istream& operator>>(istream& is, Item& i)
{
	string s;
	int ii;
	double d;
	if (is >> s >> ii >> d)
	{
		i.name = s;
		i.iid = ii;
		i.value = d;
		return is;
	}
	
	return is;

}

ostream& operator<<(ostream& os, Item& i)
{
	return os << i.name << " " << i.iid << " $" << i.value;
}

template<typename T>
void print(T t)
{
	for (auto a1 = t.begin(); a1 != t.end(); ++a1)
		cout << *a1 << endl;
}
void f_vec()
{
	string file = "itemlist.txt";
	ifstream ifs{ file };
	if (!ifs) throw runtime_error(file + " unable to be opened");

	vector<Item> iStore;
	Item i;
	while (ifs >> i)
		iStore.push_back(i);
	cout << "Initial list:\n";
	print(iStore);

	cout << "\nSorted by Name:\n";
	sort(iStore.begin(), iStore.end(), Item_namesort());
	print(iStore);

	cout << "\nSorted by ID#\n";
	sort(iStore.begin(), iStore.end(), Item_iidsort());
	print(iStore);

	cout << "\nSorted by Value:\n";
	sort(iStore.begin(), iStore.end(), Item_valuesort());
	print(iStore);

	iStore.push_back(Item{ "Horse shoe", 99, 12.34 });
	iStore.push_back(Item{ "Cannon s400", 9988, 499.95 });
	print(iStore);

	cout << "Enter a name to delete from the Item List: ";
	string s1_delete;
	getline(cin, s1_delete);
	auto ps1 = find(iStore.begin(), iStore.end(), s1_delete);
	if (ps1 != iStore.end())
		iStore.erase(ps1);
	else cout << "Error: Item " << s1_delete << " not found\n";

	cout << "Enter another name to delete from Item List: ";
	string s2_delete;
	getline(cin, s2_delete);
	auto ps2 = find(iStore.begin(), iStore.end(), s2_delete);
	if (ps2 != iStore.end())
		iStore.erase(ps2);
	else cout << "Error : Item " << s2_delete << " not found\n";

	cout << "Updated List:\n";
	print(iStore);

	cout << "Enter a couple ID# do delete items from the list:\n";
	int id1_delete = 0;
	int id2_delete = 0;
	cin >> id1_delete >> id2_delete;
	auto pid1 = find(iStore.begin(), iStore.end(), id1_delete);


	if (pid1 == iStore.end())
		cout << "Error: " << id1_delete << " ID not found\n";
	else
		iStore.erase(pid1);

	auto pid2 = find(iStore.begin(), iStore.end(), id2_delete);
	if (pid2 == iStore.end())
		cout << "Error: " << id2_delete << " ID not found\n";
	else
		iStore.erase(pid2);

	cout << "Updated list:\n";
	print(iStore);
}

void f_list()
{
	string file = "itemlist.txt";
	ifstream ifs{ file };
	if (!ifs) throw runtime_error(file + " unable to be opened");

	list<Item> iStore;
	Item i;
	while (ifs >> i)
		iStore.push_back(i);
	cout << "Initial list:\n";
	print(iStore);

	cout << "\nSorted by Name:\n";
	iStore.sort(Item_namesort());
	print(iStore);

	cout << "\nSorted by ID#\n";
	iStore.sort(Item_iidsort());
	print(iStore);
	
	cout << "\nSorted by Value:\n";
	iStore.sort(Item_valuesort());
	print(iStore);

	iStore.push_back(Item{ "Horse shoe", 99, 12.34 });
	iStore.push_back(Item{ "Cannon s400", 9988, 499.95 });
	print(iStore);

	cout << "Enter a name to delete from the Item List: ";
	string s1_delete;
	getline(cin, s1_delete);
	auto ps1 = find(iStore.begin(), iStore.end(), s1_delete);
	if (ps1 != iStore.end())
		iStore.erase(ps1);
	else cout << "Error: Item " << s1_delete << " not found\n";

	cout << "Enter another name to delete from Item List: ";
	string s2_delete;
	getline(cin, s2_delete);
	auto ps2 = find(iStore.begin(), iStore.end(), s2_delete);
	if (ps2 != iStore.end())
		iStore.erase(ps2);
	else cout << "Error : Item " << s2_delete << " not found\n";

	cout << "Updated List:\n";
	print(iStore);

	cout << "Enter a couple ID# do delete items from the list:\n";
	int id1_delete = 0;
	int id2_delete = 0;
	cin >> id1_delete >> id2_delete;
	auto pid1 = find(iStore.begin(), iStore.end(), id1_delete);


	if (pid1 == iStore.end())
		cout << "Error: " << id1_delete << " ID not found\n";
	else
		iStore.erase(pid1);

	auto pid2 = find(iStore.begin(), iStore.end(), id2_delete);
	if (pid2 == iStore.end())
		cout << "Error: " << id2_delete << " ID not found\n";
	else
		iStore.erase(pid2);

	cout << "Updated list:\n";
	print(iStore);
}

int main()
{
	//f_vec();
	//f_list();

	return 0;
}