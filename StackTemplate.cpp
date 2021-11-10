#include <iostream>
#include <sstream>	//for converting string to float
#include <string>
#include <cmath>	//for using pow method
using namespace std;


template <typename T>
class Stack {
	T* stack;
	int top = -1;
	int SIZE;

	bool isFull() {     //checks if the stack is full
		return(top == (SIZE - 1));
	}

public:
	Stack(int size = 20) {	//creates a stack with size provided or of size 20 otherwise
		SIZE = size;
		stack = new T[SIZE];
	}

	bool isEmpty() {    //checks if the stack is empty
		return (top == -1);
	}

	bool peek(T* n) //returns true if there is a value at top of the stack
	{
		if (isEmpty()) {
			return false;
		}

		*n = stack[top];
		return true;
	};

	void push(T value) {      //pushes an element on the top of the stack
		if (!isFull()) {
			stack[++top] = value;
		}
		else {
			cout << endl << "The stack is full";
		}
	}

	T pop() {    //removes and displays the element from the top of stack
		if (isEmpty()) {
			cout << endl << "The stack is empty";
			return '- 1';
		}
		else {
			T val = stack[top--];
			return val;
		}
	}

	void clear() {      //releases the memory allocated by stack
		cout << endl << "The stack has been cleared all";
		top = -1;
		delete[] stack;
	}
};

int checkPrecedence(char opr, char top) {		// 0: higher, 1: equal, 2: lower
	if ((opr == '(') || (opr == '^' && top != '^') || ((opr == '/' || opr == '*') && (top == '+' || top == '-')) || (top == ' ') || (top == '('))
		return 0;
	else if (opr == top)
		return 1;
	else
		return 2;
}

string removeExtraSpaces(string exp) {	//removes any two consecutive spaces
	string w_space = "";
	w_space.push_back(exp[0]);

	for (int i = 1; i < exp.size() + 1; i++) {
		if (!(w_space[i - 1] == ' ' && exp[i] == ' ')) {
			w_space.push_back(exp[i]);
		}
	}
	return w_space;
}

class Postfix {
	string postfixTerm = "";
	string postfix = "";
	Stack <char> operators;
	Stack <double> evaluation;
	char popped = ' ';
	char n = ' ';

public:
	string convertToPostfix(string infix)		//converts infix to postfix assuming that a valid expression is received
	{
		for (int i = 0; i < infix.size() + 1; i++)
		{
			if (isdigit(infix[i]))
				postfixTerm.push_back(infix[i]);	//append each digit to the term

			else if (!isspace(infix[i])) {

				//appends the previous term to the postfix expression

				postfix.append(postfixTerm);
				if (postfix != "") {
					postfix.append(" ");
				}
				postfixTerm = "";

				// if the stack is empty OR the top of stack is opening bracket OR
				// incoming operator has higher precedence than the top
				// then push the incoming operator to the stack

				operators.peek(&n);
				if (operators.isEmpty() || n == '(' || checkPrecedence(infix[i], n) == 0) {
					operators.push(infix[i]);
				}

				// if the incoming symbol is ')', pop the stack and print the operators until the left
				// parenthesis is found.

				else if (infix[i] == ')') {

					popped = operators.pop();

					while (popped != '(') {
						postfix.push_back(popped);
						popped = operators.pop();
					}
				}

				else {

					// if the incoming operator has the same precedence with the top of the stack then
					// pop and print the top of the stack then push the incoming operator

					if (checkPrecedence(infix[i], n) == 1) {
						postfix.push_back(operators.pop());
						operators.push(infix[i]);
					}

					// if the incoming symbol has lower precedence than the top of the stack, pop and
					// print the top of the stack.Then test the incoming operator against the new top of
					// the stack

					if (checkPrecedence(infix[i], n) == 2) {

						while (!operators.isEmpty() && checkPrecedence(infix[i], n) == 2) {
							postfix.push_back(operators.pop());
							operators.peek(&n);
						}
						operators.push(infix[i]);
					}
				}
			}
		}
		return removeExtraSpaces(postfix);
	}

	float evaluateExp(string postfix) {
		postfixTerm = "";
		float below = 0;
		float top = 0;
		float result;
		float var = 0;

		for (int i = 0; i < postfix.size() - 1; i++) {

			if (isdigit(postfix[i]))
				postfixTerm.push_back(postfix[i]);	//append each digit to the term

			else if (isspace(postfix[i])) {
				if (postfixTerm != "") {	// ignore space after any operator
					stringstream degree(postfixTerm);	//convert string to double
					degree >> var;
					evaluation.push(var);
					postfixTerm = "";
				}
			}

			else {
				top = evaluation.pop();
				below = evaluation.pop();

				if (postfix[i] == '+') {
					result = below + top;
				}
				else if (postfix[i] == '-') {
					result = below - top;
				}
				else if (postfix[i] == '*') {
					result = below * top;
				}
				else if (postfix[i] == '/') {
					result = below / top;
				}
				else if (postfix[i] == '^') {
					result = pow(below, top);
				}
				evaluation.push(result);
			}
		}
		return result;
	}
};


int main()
{
	Postfix p;
	string infix;
	string postfix;
	double ans;

	cout << "Enter the infix expression to convert it postfix: ";
	getline(cin, infix);
	postfix = p.convertToPostfix(infix);
	cout << "Postfix Expression: " << postfix << endl;
	ans = p.evaluateExp(postfix);
	cout << "Evaluation: " << ans << endl;
}