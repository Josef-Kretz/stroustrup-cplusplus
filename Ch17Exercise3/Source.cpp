#include <iostream>
#include <string>

using namespace std;

void to_lower(char* s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		char c = s[i];
		if (c >= 65 && c <= 90)
			c += 32;
		s[i] = c;
		++i;
	}
}

char* strdup1(const char* s)
{
	int i;
	for (i = 0; s[i] != '\0'; ++i);

	char* p = new char[i];
	
	for (i;i>=0;--i)
		p[i] = s[i];

	return p;
}

int c_length(const char* c)
{
	int i = 0;
	for (i; c[i]; ++i);
	return i;
}

char* findx(const char* s, const char* x)
{
	int x_length = c_length(x);
	int s_length = c_length(s);
	int check = 0;

	char* found = new char[x_length];

	for (int i = 0; s[i]; ++i)
	{
		while (s[i] == x[check])
		{
			found[check] = x[check];
			++i;
			++check;
			if (x[check] == '\0')
			{
				found[check] = '\0';
				return found;
			}
		}
		check = 0;
	}
	return nullptr;
}

char* char_in()
{
	cout << "Please input a string ending with '!':\n";
	char c;
	char* cc = new char[128];
	int count = 0;

	while (cin >> c && c != '!')
	{
		cc[count] = c;
		if (count >= 127) count = 0;
		++count;
	}

	char* returning_char = new char[count];
	for (int i = 0; i < count; ++i)
	{
		returning_char[i] = cc[i];
	}
	returning_char[count] = '\0';
	return returning_char;
}

string string_in()
{
	cout << "Please input a string ending with '!':\n";
	char c;
	string s;
	while (cin >> c && c != '!')
	{
		s += c;
	}
	return s;
}

int main()
{
	/*char c[]{ "HELLO everYBODY" };
	to_lower(c);
	cout << c << endl;

	char* cc = strdup1(c);

	cout << cc << endl;

	char tt[]{ "body" };
	char* finder = findx(c, tt);

	if (finder) cout << finder;
	else cout << "Not found";

	char* char_input = char_in();

	cout << "User input this string:\n"
		<< char_input << endl;*/

	cout << string_in() << endl;

	return 0;
}