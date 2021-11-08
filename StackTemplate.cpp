#include <iostream>
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
	Stack(int size) {
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
			cout << val;
			return val;
		}
	}

	void clear() {      //releases the memory allocated by stack
		cout << endl << "The stack has been cleared all";
		top = -1;
		delete[] stack;
	}
};

int main() {
	Stack <int> s1(5);
	int n = 0;
	for (int i = 0; i < 5; i++)
	{
		cout << i << endl;
		s1.push(i);
	}
	
	cout << endl;
	
	if (s1.peek(&n)) {
		cout << "peak is " << n << endl;
	};
	cout << endl;

	
	for (int i = 0; i < 2; i++)
	{
		s1.pop();
		cout << endl;
	}

	s1.clear();
	s1.pop();
}