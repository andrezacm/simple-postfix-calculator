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
using namespace std;

void solvePostfix(string postfixExp);  //computes the value of arithmetic
									   									//expression given in postfix format

/************************************************************
 * Stack to store operands of postfix expression            *
 ************************************************************/
class OperandStack {
	private:
		double * s;  		//pointer to 1D dynamic array for storing stack elements
		int capacity,  	//stack capacity
			t;  					//index of the top element on stack
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

int OperandStack::size() const {
	return capacity;
}

int main() {
	return 0;
}

//write additional helper functions as needed
