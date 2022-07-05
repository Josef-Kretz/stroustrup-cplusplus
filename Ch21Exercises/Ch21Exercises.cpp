#include <iostream>
#include <fstream>

#include <algorithm>
#include <string>
#include <numeric>

#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

void exercise3()
//use std::count()
{
	string filename{ "reading_gaol.txt" };

	ifstream ifs{ filename };
	if (!ifs) throw runtime_error(filename + "unopened");

	istream_iterator<string> ii{ ifs };	//start of stream
	istream_iterator<string> eos;		//equals same as end of stream

	int count = std::count(ii, eos, "gaol");
	cout << "Mentions of gaol in Reading Gaol: " << count << endl;
}

void exercise4()
//use count_if()
{
	string filename{ "reading_gaol.txt" };
	ifstream ifs{ filename };
	if (!ifs) throw runtime_error(filename + " could not be opened");

	istream_iterator<string> ii{ ifs };
	istream_iterator<string> eos;

	int count = count_if(ii, eos,
		[](const string& s) ->bool {return s.size() > 12; });

	cout << "Number of long words in Reading Gaol: " << count << endl;
}

struct Fruit {
	string name;
	int count=0;
	double unit_price=0;
	//Date last_sale_date;

	Fruit() {}

	Fruit(string n, int c, double price)
		:name(n), count(c), unit_price(price) {}
};

struct Fruit_order {
	bool operator()(const Fruit& a, const Fruit& b) const
	{
		return a.name < b.name;
	}
};

struct Fruit_comparison {
	bool operator()(const Fruit* a, const Fruit* b) const
	{
		return a->name < b->name;
	}
};

ostream& operator<<(ostream& os,const Fruit& f)
{
	return os << f.name << '\t' << f.count 
		<< " units\t" << f.unit_price << "$/unit\n";
}

void exercise6()
//set<Fruit*>, set<Fruit*< Fruit_comparison>
{
	set<Fruit, Fruit_order> inventory1; //use Fruit_order(x,y) to compare Fruits
	set<Fruit*, Fruit_comparison> inventory2; //user Fruit_comparison(x,y) to compare Fruits

	Fruit f1("Apple", 10, 3.57);
	Fruit f2("Banana", 12, 0.57);
	Fruit f3("Pineapple", 50, 9.32);
	Fruit f4("Coconut", 22, 5.44);
	Fruit f5("Date", 150, 1.33);

	inventory1.insert(f1);
	inventory1.insert(f2);
	inventory1.insert(f3);
	inventory1.insert(f4);
	inventory1.insert(f5);

	cout << "Inventory List One:\n";
	for (auto p : inventory1)
		cout << p;

	inventory2.insert(new Fruit("Peach", 20, 0.33));
	inventory2.insert(new Fruit("Mango", 5, 2.43));
	inventory2.insert(new Fruit("Lime", 50, 0.56));
	inventory2.insert(new Fruit("Lemon", 12, 0.79));
	inventory2.insert(new Fruit("Tomato", 500, 1.21));

	cout << "\n\nInventory List Two:\n";
	for (auto p : inventory2)
		cout << *p;

	inventory2.insert(&f1);
	inventory2.insert(&f2);
	inventory2.insert(&f3);
	inventory2.insert(&f4);
	inventory2.insert(&f5);

	cout << "\n\nInventory 2 updated:\n";
	for (auto p : inventory2)
		cout << *p;
}

template<typename Iter, typename T>
Iter bin_find(Iter start, Iter end, T val)
//requires Iterator Iter and element type T 
{
	auto mid = std::distance(start, end);
	auto last = end;

	while (start != end && mid != 0) {
		if (*start == val) return start;
		mid /= 2;
		auto p = start;
		advance(p, mid);
		*p > val
			? advance(end, -mid)
			: advance(start, mid);
	}
	if(mid == 0)
		if(*(--end) == val)
				return end;
	return last;
}

void exercise7()
{
	vector<int> vi{ 1,2,3,4,5,6,7,8,9,10 };

	vector<int>::iterator vip = bin_find(vi.begin(), vi.end(), 10);
	if (vip != vi.end()) cout << *vip << endl;

	list<int> li{ 1,2,3,4,5,6,7,8,9,10 };
	list<int>::iterator lit = bin_find(li.begin(), li.end(), 5);
	if (lit != li.end()) cout << "Found: " << *lit << endl;

	list<char> lc{ 'a','b','c','d','e','f','g','h','i','j','k','l' };
	list<char>::iterator lcp = bin_find(lc.begin(), lc.end(), 'z');
	if (lcp != lc.end()) cout << "Found: " << *lcp << endl;
	

}

void exercise8()
{
	string filename{ "reading_gaol.txt" };
	ifstream ifs{ filename };
	if (!ifs) throw runtime_error(filename + " cannot be opened");

	istream_iterator<string> ss{ ifs };
	istream_iterator<string> eos;

	map<string, int> words;

	while (ss != eos) {
		++words[*ss];
		++ss;
	}

	list <pair<int, string>> reversed;
	
	for (auto p : words)
		reversed.push_back(pair<int, string>(p.second, p.first));

	reversed.sort([](const pair<int, string>& a, const pair<int, string>& b) -> bool {return a.first > b.first; });
	for (auto p : reversed)
		cout << p.second << ": " << p.first << endl;
}

class Purchase {
	string product;
	double unit_price = 0.0;
	int count=0;

public:
	Purchase() {}
	Purchase(string name, double price, int stock)
		:product(name), unit_price(price), count(stock) {}

	//manipulate purchase info
	void set_name(string s) { product = s; }
	void set_price(double d) { unit_price = d; }
	void set_stock(int stock) { count = stock; }
	
	//get purchase info
	string get_name() const { return product; }
	double get_price() const { return unit_price; }
	int get_stock() const { return count; }
};

class Order
{
	string customer, address, data;
	vector<Purchase> buy;

public:
	Order() {}
	Order(string name, string street, string info)
		:customer(name), address(street), data(info) {}

	//set customer info
	void set_name(string s) { customer = s; }
	void set_address(string s) { address = s; }
	void set_data(string s) { data = s; }

	//comparison operators
	bool operator<(const Order& o) const;
	bool operator==(const Order& o) const;

	//get customer info
	string get_name() const { return customer; }
	string get_address() const { return address; }
	string get_data() const { return data; }
	double get_bill() const;
	vector<Purchase> get_copy() const { return buy; }

	//manipulate Order info
	void add_order(const Purchase p)
	{
		buy.push_back(p);
	}
	int orders() const { return buy.size(); }
	Purchase& operator[](int n)
	{
		return buy[n];
	}

	//reset object and members
	void reset()
	{
		customer.clear();
		address.clear();
		data.clear();
		buy.clear();
	}

};

bool Order::operator<(const Order& o) const
{
	return this->address < o.address;
}

bool Order::operator==(const Order& o) const
{
	return this->address == o.address
		&& this->customer == o.customer
		&& this->data == o.data;
}

double Order::get_bill() const
{
	double bill = 0;

	for (Purchase p : buy)
		bill += (p.get_price() * p.get_stock());
	return bill;
}
double calc_bill(double d, const Order& o)
{
	return d + o.get_bill();
}
istream& operator>>(istream& is, Purchase& p)
//@name, $price, #count
{
	char c; string s; double d=0; int i=0;
	if (is >> c && c == '@')
		while (c != '$' && is >> c) s += c;
	p.set_name(s);
	if (c == '$') is.putback(c);

	if (is >> c && c == '$')
		if (is >> d) p.set_price(d);

	if (is >> c && c == '#')
		if (is >> i) p.set_stock(i);

	return is;

}

istream& operator>>(istream& is, Order& o)
//"customer " ->name, { address }, ( data )
// [ purchase ]
{
	o.reset(); //clears all stored member data

	string s;
	if (is >> s && s == "customer")
		if (is >> s) o.set_name(s);

	char c;
	s = "";
	if (is >> c && c == '{')
		while (is >> c && c != '}') s += c;
	if (!s.empty()) o.set_address(s);

	s = "";
	if (is >> c && c == '(')
		while (is >> c && c != ')') s += c;
	if (!s.empty()) o.set_data(s);

	Purchase p;

	while (is>>c && c == '[')
	{
		if (is >> p) o.add_order(p);

		while (c != ']') is >> c;

		if (is >> c && c != '[') break;
		else is.putback(c);
	}

	if (c == ']') is.clear();
	else is.putback(c);

	return is;
}

ostream& operator<<(ostream& os, const Purchase& p)
{
	return os << " @" << p.get_name() << " $" << p.get_price() << " #" << p.get_stock();
}

ostream& operator<<(ostream& os, const Order& o)
{
	vector<Purchase> vp = o.get_copy();
	
	os << " customer " << o.get_name() << endl;
	os << '{' << o.get_address() << '}' << endl;
	os << '(' << o.get_data() << ')' << endl;

	if (vp.size() > 0)
		for (Purchase p : vp)
			os << '[' << p << ']' << endl;
	
	return os;
}

void exercise9()
{
	string in_file1 = "customer_log1.txt";
	ifstream ifs1{ in_file1 };

	string in_file2 = "customer_log2.txt";
	ifstream ifs2{ in_file2 };

	string out_file1 = "sorted_log1.txt";
	ofstream ofs1{ out_file1 };

	string out_file2 = "sorted_log2.txt";
	ofstream ofs2{ out_file2 };

	string log = "sorted_log.txt";
	ofstream ofs3{ log };

	vector<Order> orders1;
	list<Order> orders2;

	Order o1;
	while(ifs1>>o1)
		orders1.push_back(o1);

	while (ifs2 >> o1)
		orders2.push_back(o1);

	sort(orders1.begin(), orders1.end());
	orders2.sort();

	for (auto o : orders1)
		ofs1 << o << endl;

	for (auto o : orders2)
		ofs2 << o << endl;

	ostream_iterator<Order> oss = ofs3;

	merge(orders1.begin(), orders1.end(), orders2.begin(), orders2.end(), oss);

	double total_order = accumulate(orders1.begin(), orders1.end(), double(0), calc_bill);
	total_order = accumulate(orders2.begin(), orders2.end(), total_order, calc_bill);

	cout << "Total bill is: " << total_order << endl;

}

int main()
{
	//exercise3();
	//exercise4();

	//exercise6();
	//exercise7();

	//exercise8();
	exercise9();



	return 0;

}