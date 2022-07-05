// Ch20Exercise2
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

double* get_from_jack(int* count)
{
	constexpr int chunk = 8;

	string file_name = "d1.txt";
	ifstream ifs{ file_name };
	if (!ifs) throw runtime_error("Jack's file unopened!");

	int size = chunk;
	unique_ptr<double[]> darray{ new double[size] };
	double d = 0;
	
	for (int i = 0; ifs >> darray[i]; ++i)
	{
		*count += 1;
		if (i + 1 >= size)
		{
			unique_ptr<double[]> temp{ new double[size + chunk] };
			copy(darray.get(), darray.get() + size, temp.get());
			size += chunk;
			darray = move(temp);
		}
	}


	return darray.release();
}

vector<double>* get_from_jill()
{
	string file_name = "d2.txt";
	ifstream ifs{ file_name };
	if (!ifs) throw runtime_error("Jill's file unopened!");

	vector<double>* v = new vector<double>;
	double d = 0;
	while (ifs >> d)
		v->push_back(d);

	return v;
}

template<typename Iterator>
Iterator high(Iterator first, Iterator last)
//return an iterator to the element in [first:last) that has the highest value
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*high < *p) high = p;

	return high;
}

void fct()
{
	int jack_count = 0;

	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();

	double* jack_high = high(jack_data, jack_data + jack_count);
	vector<double>& v = *jill_data;
	double* jill_high = high(&v[0], &v[0]+v.size());

	if (jack_high && jill_high)
		cout << "Jill's high: " << *jill_high << endl
		<< "Jack's high: " << *jack_high << endl;

	if(jack_data)	delete[] jack_data;
	if(jill_data)	delete jill_data;
}


int main()
{	
	fct();

	return 0;
}
