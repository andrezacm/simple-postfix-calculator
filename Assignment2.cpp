/*
 * This project is part of the course CPSC 131 – Data Structures Concepts
 * This program is a simple calculator using stacks.
 * The calculator receive as input a math expression in postfix format.
 * And, return the result of the expression.
 *
 * Author: Andreza da Costa Medeiros
 * April 24, 2015
 *
*/

#include <iostream>
#include <ctype.h>
#include <sstream>
#include <math.h>

using namespace std;

void solvePostfix(string postfixExp);  //computes the value of arithmetic
									   									//expression given in postfix format

double calculate(double number1, double number2, char op);
																			//calculate two numbers according to
																		 // the operator
bool isNumber(string number); //verify if a string is a number

/************************************************************
 * Stack to store operands of postfix expression            *
 ************************************************************/
class OperandStack {
	private:
		double * s;  		//pointer to 1D dynamic array for storing stack elements
		int capacity,  	//stack capacity
			t;						//index of the top element on stack
		void growStack(int newCapacity);  //increases the stack if it is full
							//must be called from the push function if the stack is full

	 public:
		OperandStack(){ capacity = 0; s = NULL; t = -1; };
		OperandStack(int capacity);
	  ~OperandStack();
		int 	 size() 	 const;  	//return the number of elements in the stack
	  bool 	 isFull()  const;
		bool 	 isEmpty() const;
		double top() 		 const;  //returns the element at the top of the stack
					 									//without removing it from the stack
	  void push(double x);
	  void pop();
};

/*
 * OperandStack constructor
 * Inputs: stack capacity
 * Return: nothing
 *
 */
OperandStack::OperandStack(int cap) {
	capacity = cap;
	s = new double[capacity];
	t = -1;
}

/*
 * OperandStack destructor
 * Inputs: nothing
 * Return: nothing
 *
 */
OperandStack::~OperandStack() {
	capacity = 0;
	t = -1;
	delete s;
	s = NULL;
}

/*
 * OperandStack size will return the size of the stack
 * Inputs: nothing
 * Return: stack size
 *
 */
int OperandStack::size() const {
	return t+1;
}

/*
 * OperandStack isFull check if the stack reached the capacity
 * Inputs: nothing
 * Return: boolean
 *
 */
bool OperandStack::isFull() const {
	return (capacity - size()) == 0;
}

/*
 * OperandStack isEmpty check if the stack is empty
 * Inputs: nothing
 * Return: boolean
 *
 */
bool OperandStack::isEmpty() const {
	return (t == -1);
}

/*
 * OperandStack top return the element on top of the stack
 * Inputs: nothing
 * Return: element on top
 *
 */
double OperandStack::top() const {
	return s[t];
}

/*
 * OperandStack push will insert a new element on top of the stack
 * Inputs: element
 * Return: nothing
 *
 */
void OperandStack::push(double x) {
	if(isFull()) growStack(capacity * 2);
	t++;
	s[t] = x;
}

/*
 * OperandStack pop will remove an element on top of the stack
 * Inputs: nothing
 * Return: element
 *
 */
void OperandStack::pop() {
	if (!isEmpty()) {
		s[t] = 0;
		t--;
	} else {
		throw "error – malformed expression";
	}
}

/*
 * OperandStack growStack will increase the size of the stack
 * Inputs: the new size
 * Return: nothing
 *
 */
void OperandStack::growStack(int newCapacity) {
	double * newStack = new double[newCapacity];
	for (int i=0; i<(t+1); i++) newStack[i] = s[i];
	delete s;
	s = newStack;
}

int main() {

	while(true) {
		cout << endl << "Enter a postfix expression: ";

		string postfix;
		getline(cin, postfix);

		if (postfix == "q") break;

		cout << "Result: ";

		try {
			solvePostfix(postfix);
		} catch (const char* msg) {
	  	cerr << msg << endl;
	  }
	}

	return 0;
}

//helper functions

/*
 * solvePostfix computes the value of an arithmetic expression given in postfix notation
 * Inputs: postfix expression
 * Return: nothing
 *
 */
void solvePostfix(string postfixExp) {
	OperandStack s = OperandStack(2);

	//split string by space
	istringstream iss(postfixExp);

	while (iss) {
		string word;
		iss >> word;

		if(iss < 1) break;

		if (isNumber(word)) {
			s.push(atof(word.c_str()));

		} else {
			double top1, top2, result;

			top1 = s.top();
			s.pop();

			top2 = s.top();
			s.pop();

			result = calculate(top2, top1, word[0]);
			s.push(result);
		}
	}

	if (s.size() > 1) throw "error – malformed expression";

	cout << s.top() << endl;

	s.~OperandStack();
}

/*
 * calculate solves the equation
 * Inputs: two numbers and one operator
 * Return: the result
 *
 */
double calculate(double number1, double number2, char op) {
	double result;
	switch (op) {
		case '+': result = number1 + number2; break;
		case '-': result = number1 - number2; break;
		case '*': result = number1 * number2; break;
		case '/': result = number1 / number2; break;
		case '^': result = pow(number1, number2); break;
		default : result = 0;
	}
	return result;
}

/*
 * isNumber verify if a string is a number
 * Inputs: one string
 * Return: boolean
 *
 */
bool isNumber(string number) {
	bool isnumber = true;
	for(int i=0; i<number.length(); i++) {
		if (!isdigit(number[i])) isnumber = false;
	}
	return isnumber;
}
