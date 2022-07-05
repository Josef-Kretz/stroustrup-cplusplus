#include <iostream>
#include <string>

char* strdup1(const char* cs)
//creates a copy of a c-style string
{
	int count = 0;
	while (*cs)
	{
		++count;
		++cs;
	}
	cs -= count;

	char* cc = new char[count+1];
	while (*cs)
	{
		*cc = *cs;
		++cc;
		++cs;
	}
	*cc = '\0';
	cc -= count;

	return cc;
}

char* findx(const char* s, const char* x)
//finds first occurence of a c-style string
{
	int size_s = 0;
	int size_x = 0;

	while (*s)
	{
		++size_s;
		++s;
	}
	while (*x)
	{
		++size_x;
		++x;
	}
	s -= size_s;
	x -= size_x;
	char* return_copy = strdup1(x); //creates a copy of match to return;

	int reset_x = 0;
	while (*s)
	{
		while (*s == *x)
		{
			++s; ++x; //increment pointers together
			++reset_x; //used to reset x pointer if match fails
			if (*x) return return_copy;
		}
		x -= reset_x;
		++s;
	}

	return nullptr;
}

int strcmp1(const char* s1, const char* s2)
//compares s1 against s2
//negative int = s1>s2, 0 int = s1 = s2, positive int = s1 < s2
{
	int size_1 = 0;
	int size_2 = 0;
	while (*s1) {
		++size_1;
		++s1;
	}
	s1 -= size_1;
	while (*s2) {
		++size_2;
		++s2;
	}
	s2 -= size_2;

	int count = 0;
	while (*s1 && *s2)
	{
		if (*s1 < *s2) return -1;
		if (*s1 > *s2) return 1;
		if (*s1 == *s2)
		{
			++s1; ++s2;
			++count;
		}
	}
	if (size_1 == size_2) return 0;
	if (count == size_1) return -1;
	if (count == size_2) return 1;

	return 0;
}

int c_size(const char* s)
{
	int count = 0;
	while (*s)
	{
		++count;
		++s;
	}
	s -= count;
	return count;
}

char* c_cat_dot(const char* s1, const char* s2, const char* separ)
{
	int size_1 = c_size(s1);
	int size_2 = c_size(s2);
	int size_separ = c_size(separ);
	int end_size = size_1 + size_2 + size_separ;

	char* final_c = new char[end_size];
	while (*s1)
	{
		*final_c = *s1;
		++s1;
		++final_c;
	}
	s1 -= size_1;

	while (*separ)
	{
		*final_c = *separ;
		++separ;
		++final_c;
	}
	separ -= size_separ;

	while (*s2)
	{
		*final_c = *s2;
		++s2;
		++final_c;
	}
	s2 -= size_2;

	*final_c = '\0';
	final_c -= end_size;

	return final_c;

}

std::string cat_dot(const std::string& s1, const std::string& s2, const std::string& separator)
{
	return s1 + separator + s2;
}

int main()
{
	try {
		//exercise 1
		char first_cstring[] { "Hello World" };	//doesn't create on free store, can't use delete
		//delete or delete[] first_cstring won't work, not created using NEW
		char* second_cstring = strdup1(first_cstring);//object created on free store, CAN use delete

		std::cout << first_cstring << std::endl;
		std::cout << second_cstring << std::endl;

		//exercise 2
		char third_cstring[]{ "ello" };
		std::cout << findx(second_cstring, third_cstring) << std::endl;

		//exercise 3
		std::cout << "Hello World vs Hello World: " << strcmp1(first_cstring, second_cstring) << std::endl;
		std::cout << "Hello World vs ello " << strcmp1(first_cstring, third_cstring) << std::endl;
		std::cout << "bees vs aardvark " << strcmp1("bees", "aardvark") << std::endl;

		//exercise 4, use bad c style strings
		/*
		char* c1 = new char[4] { 'a', 'b', 'c', 'd' };
		char c2[] { "abcdefghijklmno" };
		std::cout << "Trying to break functions:\n";
		std::cout << "strdup1() " << strdup1(c1) << std::endl;
		std::cout << "findx() " << findx(c1, c2) << std::endl;
		std::cout << "strcmp() " << strcmp1(c1, c2) << std::endl;*/

		std::cout << "Test cat_dot() " << cat_dot("Niels", "Bohr", " dot ") << std::endl;

		char* cat1 = c_cat_dot(third_cstring, second_cstring, " BEAUTIFUL, ");
		std::cout << cat1 << std::endl;

		return 0;
	}
	catch (std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Error\n";
	}

}