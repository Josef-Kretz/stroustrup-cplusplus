#include <iostream>
#include <fstream>

#include <algorithm>
#include <numeric>

#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

template<typename In, typename T>
//requires Input_iterator<In>()
//	&& Equality_comparable<Value_type<T>>()
In find1(In first, In last, const T& val)
{
	while (first != last && *first != val) ++first;
	return first;
}

template<typename In, typename T>
// requires Input_iterator<In>()
//		&&Equality_comprarble<Value_type<T>>()
In find2(In first, In last, const T& val)
{
	for (In p = first; p != last; ++p)
		if (*p == val) return p;
	return last;
}

struct Record
{
	double unit_price;
	int units;

	Record()
		:unit_price(0), units(0) {}

	Record(int unit, double price)
		:units(unit), unit_price(price) {}
};

double price(double v, const Record& r)
{
	return v + r.units * r.unit_price; //calculate price and accumulate
}

void f_trythis1()
{
	vector<int> vi1{ 1,2,3,4,5,6,7,8,9,10 };

	vector<int>::iterator pvi1 = find1(vi1.begin(), vi1.end(), 10);
	vector<int>::iterator p2vi1 = find2(vi1.begin(), vi1.end(), 1);

	if (pvi1 != vi1.end()) cout << "Found value: " << *pvi1 << endl;
	if (p2vi1 != vi1.end()) cout << "Found value: " << *p2vi1 << endl;
}

void f_trythis2()
{
	vector<Record> vr;
	vr.push_back(Record(10, 1.1));
	vr.push_back(Record(1, 2.2));
	vr.push_back(Record(3, 4.50));
	vr.push_back(Record(10, 5.5));

	double total = accumulate(vr.begin(), vr.end(), 0.0, price);
	cout << "The total price is: " << total << endl;
}

double weighted_value(
	const pair<string,double>& a,
	const pair<string,double>&b)
	//extract values and multiply
{
	return a.second * b.second;
}

void f_trythis3()
{
	map<string, double> dow_price = {	//DOW Jones Industrial Index (symbol,price)
		{"MMM", 81.86},
		{"AA", 34.69},
		{"MO", 54.45},
		{"GME", 211.37},
		{"AMC", 58.18}
	};

	map<string, double> dow_weight = {
		{"MMM", 5.8549},
		{"AA", 2.4808},
		{"MO", 3.8940},
		{"GME", 1.1117},
		{"AMC", 1.222}
	};

	map<string, string> dow_name = {
		{"MMM", "3M Co."},
		{"AA", "Alcoa Inc."},
		{"MO", "Altria Group Inc."},
		{"GME", "Gamestop"},
		{"AMC", "American Media Corporation"}
	};

	double alcoa_price = dow_price["AA"];

	for (const auto& p : dow_price)
	{
		const string& symbol = p.first; //ticker symbol
		cout << symbol << '\t' << p.second << '\t'
			<< dow_name[symbol] << endl;
	}

	double dji_index = inner_product(dow_price.begin(), dow_price.end(),	//all companies
		dow_weight.begin(),	//company weight
		0.0,				//initial value
		plus<double>(),		//add(as usual)
		weighted_value);	//extract values and weights, multiply together

	cout << "Total weighted DJI Index: " << dji_index << endl;

}

void f_trythis4()
{
	unordered_map<string, int> num_seq = {
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5}
	};

	for (const auto& p : num_seq)
		cout << p.first << '\t' << p.second << endl;
}

void f_trythis5()
{
	string from, to;
	cin >> from >> to;	//get source and target files

	ifstream ifs{ from };	//open input stream
	ofstream ofs{ to };		//open output stream

	istream_iterator<string> ii{ ifs };	//input iterator for stream
	istream_iterator<string> eos;		//input sentinel
	ostream_iterator<string> oo{ ofs, "\n" }; //output iterator for stream
	
		//proper code for exercise
	vector<string> b{ ii, eos };	//b is initialized from input
	sort(b.begin(), b.end());		//sort the buffer
	unique_copy(b.begin(), b.end(), oo);	//copy buffer to output
	

	/*//intentionally coded to overflow buffer
	unsigned int max_size = 25;
	vector<string> b{ max_size };
	copy(ii, eos, b.begin());*/
}

int main()
{
	//f_trythis1();
	//f_trythis2();
	//f_trythis3();
	//f_trythis4();
	f_trythis5();


	return 0;
}