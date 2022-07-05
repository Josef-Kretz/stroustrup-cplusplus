#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template<typename T> class allocat
{
public:

	T* allocate(int n);				//allocate space for n objects of type T
	void deallocate(T* p);	//deallocate n objects of type T starting at p

	void construct(T* p, const T& v);	//construct a T with the value v in p
	void destroy(T* p);					//destroy the T in p
};

template<typename T>
T* allocat<T>::allocate(int n)
{
	T* p = static_cast<T*>(malloc(n * sizeof(T)));
	if (p == nullptr) throw runtime_error("Memory allocation error");
	return p;
}

template<typename T>
void allocat<T>::deallocate(T* p)
{
	free(p);
}

template<typename T>
void allocat<T>::construct(T* p, const T& v)
{
	new(p) T{ v };
}

template<typename T>
void allocat<T>::destroy(T* p)
{
	p->~T();
}

template<typename T, typename A = allocat<T>>
class vec
{
	A alloc;	//use allocate to handle memory for elements
	int sz;		//size of vec
	T* elem;	//a pointer to the elements
	int space;	//size + free space

public:
	vec() :sz{ 0 }, elem{ nullptr }, space{ 0 } {}
	explicit vec(int s) : sz{ s }, elem{ new T[s] }, space{ s }
	{
		for (int i = 0; i < sz; ++i) alloc.construct(&elem[i], T());	//initialize all elements
	}

	vec(const vec&);			//copy constructor
	vec& operator=(const vec&);	//copy assignment

	vec(vec&&);				//move constructor
	vec& operator=(vec&&);	//move assignment

	~vec() { delete[] elem; }	//destructor

	T& at(int n);	//checked access return reference
	const T& at(int n) const;

	T& operator[](int n) { return elem[n]; }	//unchecked access return reference
	const T& operator[](int n) const { return elem[n]; }

	int size() const { return sz; }		//current size
	int capacity() const { return space; }

	void resize(int newsize, T val = T());	//growth
	void push_back(const T& d);
	void reserve(int newalloc);
};

template<typename T, typename A>
void vec<T, A>::reserve(int newalloc)
{
	if (newalloc <= space) return;	//never decrease allocation
	T* p = alloc.allocate(newalloc);	//allocate new space
	for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]);	//copy
	for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);			//destroy
	alloc.deallocate(elem);	//deallocate old space
	elem = p;
	space = newalloc;
}

template<typename T, typename A>
void vec<T, A>::push_back(const T& val)
{
	if (space == 0) reserve(8);		//start with space for 8 elements
	else if (sz == space) reserve(2 * space);	//get more space
	alloc.construct(&elem[sz], val);	//add val at end
	++sz;	//increase size
}

template<typename T, typename A>
void vec<T, A>::resize(int newsize, T val )
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], val); //construct
	for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);	//destroy
	sz = newsize;
}

template<typename T, typename A>
T& vec<T, A>::at(int n)
{
	if (n < 0 || sz <= n) throw runtime_error(n + " inaccessible");
	return elem[n];
}

template<typename T, typename A>
const T& vec<T, A>::at(int n) const
{
	if (n < 0 || sz <= n) throw runtime_error(n + " inaccessible");
	return elem[n];
}

template<typename T, typename A>
vec<T,A>& vec<T, A>::operator=(const vec<T,A>& a)
{
	T* p = new T[a.sz];		//allocate new space
	for (int i = 0; i < a.sz; ++i) p[i] = a.elem[i];
	delete[] elem;
	space = sz = a.sz;
	elem = p;
	return *this;
}

template<typename T, typename A>
vec<T, A>::vec(const vec& arg)
	:sz{ arg.sz }, elem{ new T[arg.sz] }
{
	copy(arg.elem, arg.elem+sz, elem);
}

template<typename T, typename A>
vec<T,A>::vec(vec&& a)
	:sz{ a.sz }, elem{ a.elem }	//copy a's elem and sz
{
	a.sz = 0;		//make a empty
	a.elem = nullptr;
}

template<typename T, typename A>
vec<T, A>& vec<T, A>::operator=(vec&& a) //move a to this vector
{
	delete[] elem;	//deallocate old space
	elem = a.elem;	//copy a's elem and sz
	sz = a.sz;
	a.elem = nullptr;	//make a empty
	a.sz = 0;
	return *this;		//return self reference
}

int main()
{
	try {
		vec<int> itest1(5);
		
		itest1.push_back(7);
		cout << itest1[5] << endl;

		vec<int> itest2 = itest1;
		itest1[5] = 42;
		vec<int> itest3(20);
		itest3 = itest1;
		itest1[5] = 9000;
		cout << "#2 " << itest2[5] << endl
			<< "#1 " << itest1[5] << endl
			<< "#3 " << itest3[5] << endl;

		itest1.resize(25);
		itest1[20] = 999;
		cout << itest1[20];
	}
	catch (runtime_error& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "Error";
	}
	return 0;
}