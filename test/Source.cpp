
#pragma once
#include <Windows.h>
#include <vector>
#include <sstream>

#include "dts.h"
#include "vector.h"
#include "list.h"
#include "dtstring.h"
#include "map.h"
#include "htam.h"
using namespace htam;
using namespace std;
using namespace dts;

#define pause system("pause")
#define cls system("cls");

bool checkExpressionEncasing(Stack<char>& expression, char currChar, bool encased = false) {
	if (!expression.count()) return false;

	Vector<char> encaseBegins = { '(', '{', '\'', '"', '<', '[' };
	Vector<char> encaseEnds = { '\)', '\}', '\'', '"', '>', ']' };
	Map<char, char> encasings;
	for (int i = 0; i < encaseBegins.size(); i++) encasings[encaseEnds[i]] = encaseBegins[i];
	
	char last;  
	while (expression.count() != 0) {
		last = expression.pop();
		
		if (encaseBegins.find(last) != -1 && currChar == '-') {
			currChar = last; // если начинаетс€ новое внешнее поле
			continue;
		}
		// —отни тыс€ч точек выхода, но иначе никак
		if (currChar == encasings[last]) { // ≈сли последний символ закрывающий
			if (encased) return true; 
			else currChar = '-';
		} // если last Ч закрывающий символ не дл€ текущего символа
		else if (!checkExpressionEncasing(expression, last, true)) return false; // если внутренний символ не закрыт, выражение априори неправильное	
	}
	return currChar == '-';
}

bool checkExpression(String expString) {
	if (expString.size() == 0) return false;
	Stack<char> signs;
	for (int i = expString.size()-1; i >=0; i--) {
		switch (expString[i]) {
			case '{': case '}': case '(': case ')': case '"': case '\'': case '<': case '>': case '[': case ']': signs.push(expString[i]); break;
		}
	}
	if (signs.count() == 0) return false;
	return checkExpressionEncasing(signs, signs.pop());
}

// doesn't work
class Calculator {
private:
public:
	static int stackifyExp(String expString) {
		if (expString.size() == 0) return false;

		Queue<char> signs;
		
		for (int i = 0; i < expString.size(); i++) {
			switch (expString[i]) {
			case '+': case '-': case '/': case '*': {
				signs.enqueue(expString[i]); 
				expString[i] = ' ';
				break;
			}
			}
		}
		Queue<int> arguments;
		int number;
		
		std::streambuf* orig = std::cin.rdbuf();
		std::istringstream input(expString, 1);
		std::cin.rdbuf(input.rdbuf());
		while (cin >> number) {
			arguments.enqueue(number);
		}
		std::cin.rdbuf(orig);
		
		return evalExp(signs, arguments, arguments.dequeue());
	}

	static int evalExp(Queue<char>& signs, Queue<int>& arguments, int left, bool consecutive = false) {
		if (arguments.count() > 0 && arguments.count() > 0) {
			int right = arguments.dequeue();
			char sign = signs.dequeue();

			if (signs.count() > 0 && arguments.count() > 0) {
				
				if (signs.last() == '*' || signs.last() == '/') {
					right = evalExp(signs, arguments, right, true);
					return evalExp(signs, arguments, performOperation(left, right, sign));
				}
				else {
					left = performOperation(left, right, sign);
					if(consecutive) return left;
				}
			}
			return performOperation(left, right, sign);
		}
	}

	static int performOperation(int left, int right, char sign) {
		switch (sign) {
		case '+':
			return left + right;
			break;
		case '-':
			return left - right;
			break;
		case '/':
			return left  /right;
			break;
		case '*':
			return left * right;
			break;
		}
	}
};

enum WareType {
	Meat, Milk, Water, Juice
};




int main() {
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251); SetConsoleOutputCP(1251);

	String a = "я получил власть";
	a.append(", котора€ и не снилась моему отцу.");
	cout << a << endl;
	/*Map<int, int> bt;
	for (int i = 1; i <= 100; i++) {
		bt[i] = i;
	}
	bt.print();
	pause;
	cls;
	bt.remove(64);
	bt.remove(63);
	bt.print();
	pause;
	bt.clear();
	cls;
	for (int i = 1; i <= 10000; i++) bt[i] = i;
	bt.print();*/
}