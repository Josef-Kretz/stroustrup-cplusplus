#include <iostream>
#include <string>

using namespace std;

void error(string s)
{
	cerr << "Error: " << s << endl;
}

int main()
{
	cout << "Please enter an expression:\n";
	cout << "End expression with an 'x': ";
	int lval = 0;
	int rval;
	cin >> lval; //read leftmost operand
	if (!cin)error("no first operand");
	for (char op; cin >> op;) { //read operator and righthand operand repeatedly
		if (op != 'x')cin >> rval;
		if (!cin)error("no second operand");
		switch (op) {
		case '+':
			lval += rval; //add: lval = lval + rval
			break;
		case'-':
			lval -= rval; //subtract: lval = lval - rval
			break;
		case'*':
			lval *= rval; //multiply: lval = lval * rval
			break;
		case'/':
			lval /= rval; //divide: lval = lval / rval
			break;
		default:	//not another operator: print result
			cout << "Result: " << lval << endl;
			return 0;
		}
	}
	error("Bad expression");

}