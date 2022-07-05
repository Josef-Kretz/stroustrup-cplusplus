#include <iostream>
#include <string>
#include <vector>

#include "Chrono.h"

using namespace std;
class ISBN 
{
	int n1, n2, n3;
	char x;
	string code;

public:
	ISBN() {}
	ISBN(int num1, int num2, int num3, char xx)
		:n1(num1), n2(num2), n3(num3), x(xx)
	{
		code = to_string(n1) + '-' + to_string(n2) + '-' + to_string(n3) + '-' + x;
	}

	string properCode() { return code; }
};

enum class Genre {
	fiction = 1, nonfiction, periodical, biography, children
};

class Book
{
	string barcode, title, author, copyright;
	ISBN storedISBN;

	Genre bookType;
	bool bookIsIn = true;

public:
	Book() {}
	Book(ISBN bCode, string t, string a, string cpy, Genre bookTy);

	string getISBNstring() const { return barcode; }
	
	string getTitle() const { return title; }
	string getAuthor() const { return author; }
	string getCopyRight() const { return copyright; }
	Genre getGenre() const { return bookType; }
	bool getBookStatus() const { return bookIsIn; }
	
	void flipBookStatus() { bookIsIn = !bookIsIn; }

};


Book::Book(ISBN bCode, string t, string a, string cpy, Genre bookTy)
	: storedISBN(bCode), title(t), author(a), copyright(cpy), bookType(bookTy)
{
	barcode = bCode.properCode();
}


bool operator == (const Book& b1, const Book& b2)
{
	return b1.getISBNstring() == b2.getISBNstring();
}

bool operator != (const Book& b1, const Book& b2)
{
	return !(b1 == b2);
}

ostream& operator <<(ostream& os, const Genre& g)
{
	switch (g)
	{
	case Genre::fiction:
		return os << "fiction";
		break;
	case Genre::nonfiction:
		return os << "nonfiction";
		break;
	case Genre::periodical:
		return os << "periodical";
		break;
	case Genre::biography:
		return os << "biography";
		break;
	case Genre::children:
		return os << "children";
		break;
	default:
		return os << "Genre not found";
		break;
	}


}

ostream& operator <<(ostream& os, const Book& b)
{
	return os << "ISBN: " << b.getISBNstring() << endl
		<< "Title: " << b.getTitle() << endl
		<< "Author: " << b.getAuthor() << endl
		<< "Genre: " << b.getGenre() << endl;
}

ISBN barcodeReader(string s)
{
	vector<int> nums;
	vector<string> lines;
	string temp;

	while (nums.size() != 3)
	{
		for (char c : s)
		{
			if (c != '-' && isdigit(c))
				temp += c; 
			else if(c == '-')
			{
				if(temp != "") lines.push_back(temp);
				temp = "";
			}
			else
			{
				if (isalpha(c) || isdigit(c))
				{
					temp = c;
					lines.push_back(temp);
				}
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			bool test = true;
			for (char c : lines[i])
			{
				if (!(isdigit(c))) test = false;
			}
			if (test) nums.push_back(stoi(lines[i]));
		}
	}

	if (lines.size() >= 4)
	{
		char c = lines[3][0];
		if(nums.size() > 2) return ISBN(nums[0], nums[1], nums[2], c);
	}
	throw runtime_error("Invalid ISBN\n");
}

class Patron
{
	string name;
	string cardNumber;
	double fee =0;

public:
	Patron() {}
	Patron(string n, string cn)
		:name(n), cardNumber(cn) {}

	string getName() const { return name; }
	string getCard() const { return cardNumber; }
	double getFee() const { return fee; }

	void setFee(double d) { fee = d; }
};

bool hasFee(const Patron& p) 
{
	if (p.getFee() > 0) return true;
	return false;
}

bool operator==(const Patron& p1, const Patron& p2)
{
	return (p1.getCard() == p2.getCard());
}

bool operator !=(const Patron& p1, const Patron& p2)
{
	return !(p1 == p2);
}
class Library:
{
	vector<Book> bookLog;
	vector<Patron> patronLog;
	struct Transaction;
	vector<Transaction> ledger;
	Library() {}
public:
	
	Library(vector<Book> bv, vector<Patron> pv, vector<Transaction> lv)
		:bookLog(bv), patronLog(pv), ledger(lv) {}

	void addBook(Book);
	void addPatron(Patron);

	bool hasBook(const Book& b) const;
	bool hasPatron(const Patron& p) const;
	void feesOwed() const;

	void lendBook(const Patron&, const Book&, Chrono::Date);

};

bool Library::hasBook(const Book& b) const
{
	for (Book bb : bookLog)
		if (bb == b) return true;

	return false;
}
bool Library::hasPatron(const Patron& p) const
{
	for (Patron pp : patronLog)
		if (pp == p) return true;
	return false;
}
void Library::feesOwed() const
{
	for (Patron p : patronLog)
		if (hasFee(p)) cout << p.getName() << " owes $" << p.getFee() << endl;
}
void Library::lendBook(const Patron& p, const Book& b, Chrono::Date)
{
	try {
		bool h = hasBook(b);
	}
}

struct Library::Transaction
{
	Book borrowed;
	Patron lentOut;
	Chrono::Date dayLent;

	Transaction(Library L, Book b, Patron p, Chrono::Date day);

};

Library::Transaction::Transaction(Library L, Book b, Patron p, Chrono::Date day)
{
	//constructor for date checks validity
	//check if book is available
	bool h = hasBook(b);
	if (!L.hasBook(b)) throw runtime_error("Book is not in Library catalogue");
	if (!b.getBookStatus()) throw runtime_error("Book is lent out");

	//check is patron can take (no late fees)
	if (!L.hasPatron(p)) throw runtime_error("Patron does not exist");
	if (hasFee(p)) throw runtime_error("Patron owes fees, cannot borrow books");
	
	borrowed = b;
	lentOut = p;
	dayLent = day;
}

int main()
{
	string test{ "1234-4321-1357-H" };

	try {
		ISBN codeTest = barcodeReader(test);

		Book testBook(codeTest, "Harry Potter", "JK Rowling", "1997-ALL", Genre::fiction);
		cout << testBook;
	}
	catch (runtime_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unknown error\n";
	}
	

	return 0;

}