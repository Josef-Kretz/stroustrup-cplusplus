#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

double maxv(vector<double> large);

template<typename T>
void Printer(const T& info) //prints out vectors
{
	for (auto num : info) cout << num << endl;
}

void PriceWeight()
{
	double price = 0;
	double weight = 0;

	vector<double> prices;
	vector<double> weights;
	vector<double> index;

	cout << "Input the price and weight of each item:\n";
	while (cin >> price >> weight)
	{
		prices.push_back(price);
		weights.push_back(weight);
	}

	if (!(prices.size() == weights.size()) || prices.empty()) throw runtime_error("User input error");

	for (int i = 0; i < prices.size(); ++i)
		index.push_back(prices[i] * weights[i]);

	cout << "Index of all input:\n";
	Printer(index);

	cout << "The largest index is: " << maxv(index) << endl;

}

double maxv(vector<double> large)
{
	if (large.empty()) throw runtime_error("Passed empty vector");

	double temp = large[0];

	for (double d : large)
	{
		if (d > temp)
			temp = d;
	}

	return temp;
}

struct Averages
{
	double smallest;
	double largest;
	double mean;
	double median;

	Averages(double small, double large, double means, double media)
		:smallest(small), largest(large), mean(means), median(media) {}
};

Averages RapidMaths(vector<double> vec)
{
	if (vec.empty()) throw runtime_error("Passed empty vector");

	double large, small, mean, median, total;
	large = vec[0];
	small = vec[0];
	mean = 0;
	median = 0;
	total = 0;

	for (double d : vec) //finds largest, smallest, and sum total
	{
		if (d > large)
			large = d;
		if (d < small)
			small = d;
		total += d;
	}

	mean = (total / vec.size());
	total = 0;

	sort(vec.begin(), vec.end());
	int mid = vec.size() / 2;
	if (mid > 0 && vec.size()>1) //ensure vector has enough elements for calculation
	{
		total = vec[mid - 1] + vec[mid] + vec[mid + 1];
		total /= 3;
	}

	if (vec.size() < 2) median = vec[0]; //incase vector is only 1 element 
	else if (vec.size() > 1) median = total;

	return Averages(small, large, mean, median);
}

void PrintAverages(Averages ave)
{
	cout << "Smallest: " << ave.smallest << endl;
	cout << "Largest: " << ave.largest << endl;
	cout << "Mean: " << ave.mean << endl;
	cout << "Median: " << ave.median << endl;
}

void print_until_s(vector<string> v, string quit)
{
	for(string s: v)
	{
		if (s == quit) return;
		cout << s << '\n';
	}
}

void print_until_ss(vector<string> v, string quit)
{
	int count = 0;

	for (string s : v)
	{
		if (s == quit) ++count;
		if (count >= 2) return;
		cout << s << endl;
	}
}

struct AverageString { //easy way of returning all string values from one function
	string longest, shortest, first, last;

	AverageString(string longs, string shorts, string firsts, string lasts)
		:longest(longs), shortest(shorts), first(firsts), last(lasts) {}
};

vector<int> CharCounter(vector<string> vec) //finds string length and stores in vector
{
	vector<int> chars;
	for (string s : vec)
	{
		chars.push_back(s.size());
	}

	return chars;
}

AverageString StringAve(vector<string> vec)
{
	vector<int> charCount = CharCounter(vec);
	if (vec.empty() || charCount.empty()) throw runtime_error("Empty vector");

	//take first element of vector to initialize each variable
	int longest = charCount[0]; 
	int shortest = charCount[0];
	string longs = vec[0];
	string shorts = vec[0];

	string first = vec[0];
	string last = vec[0];

	//compares current vector element against the first variable
	//to find longest, shortest, first and last
	for (int i = 0; i < charCount.size(); ++i)
	{
		if (charCount[i] > longest)
		{
			longest = charCount[i];
			longs = vec[i];
		}
		if (charCount[i] < shortest)
		{
			shortest = charCount[i];
			shorts = vec[i];
		}

		if (vec[i] < first)
			first = vec[i];
		if (vec[i] > last)
			last = vec[i];
	}

	return AverageString(longs, shorts, first, last);

}

void PrintString(AverageString aveS)
{
	cout << "Longest String: " << aveS.longest << endl
		<< "Shortest String: " << aveS.shortest << endl
		<< "Lexographically first: " << aveS.first << endl
		<< "Lexographically last: " << aveS.last << endl;
}

void Prism(const string xenon)
{
	cout << xenon;
}
int main()
{
	//PriceWeight();

	//vector<double> userList{ 10, 11, 9, 4, 18,20,900 };
	//PrintAverages(RapidMaths(userList));

	//vector<string> strings{ "hi", "hello world", "xoey", "goodbye", "arichi", "nemsibad", "goodbye", "mark ruffalo", "kurt cobain"};
	//print_until_ss(strings, "goodbye");
	//PrintString(StringAve(strings));

	Prism("oop");

	return 0;
}