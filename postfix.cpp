#include <iostream.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <stack.h>
using namespace std;

int isOperator(char s) {
	if( s=='*' || s=='-' || s=='+' ) {
		return 1;
	} else {
		return 0;
	}
}

int isOperand(char s) {
	if(s=='0' || s=='1' || s=='2'|| s=='3' || s=='4' || s=='5' || s=='6' || s=='7' || s=='8' || s=='9' ) {
		return 1;
	} else {
		return 0;
	}
}

int performOperation(int a, int b, char operand) {
	if(operand == '+') {
		return (a + b);
	} else if( operand == '-') {
		return (a - b);
	} else if ( operand == '*') {
		return (a * b);
	} else {
		return 0;
	}
}

void strip(string &s) {
	for(int i =0; i < s.length(); i++) {
		if(!isOperand(s[i]) && !isOperator(s[i]) ) {
			s.erase(i,1);
		}
	}
}

int errorChecking(string s) {
	int operand =0;
	int operate = 0;
	for(int i = 0; i < s.length(); i++) {
		if( isOperand(s[i]) ) operand++;
		else if( isOperator(s[i]) ) operate++;
		// check if there are ever as many operators as operands at ANY point in the equation
		// if so, give error
		if(operand <= operate) break;
	}
	if(operand == operate+1) return 1;
	else return 0;
}

int main() {

	string equation = "";
	string input = " ";
	stack<char> parsed;
	int x;
	int y;
	int holder;
	char charholder;
	int result = 0;

	while(equation != "q") {
		cout << "\n\tPlease enter a postfix equation (q to quit): ";
		cin >> equation;
		if(equation == "q") break;
		strip(equation);
		if(errorChecking(equation) ) {
			for(int i =0; i < equation.length(); i++) {
				if( isOperand(equation[i]) ) {
					parsed.push( equation[i]); 
				} else if(isOperator(equation[i]) ) {
					x = parsed.top();
					x -= 48;
					parsed.pop();
					y = parsed.top();
					y-=48;
					parsed.pop();
					holder = performOperation(x, y, equation[i]);
					charholder = '0' + holder;
					parsed.push( charholder );
				}
			} // eval
			result = parsed.top() - 48;
			cout << "\n\t" << equation << " = " << result << endl;
		} else {
			cout << "\n\tThat is not a valid equation.\n\n\t";
		} // testing
	} // while
	cout << "\n\n\tDone!";
	getch();
	return 0;
}
