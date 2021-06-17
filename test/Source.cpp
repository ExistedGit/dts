
#include "dts.h"
#include <Windows.h>
using namespace std;
using namespace dts;

int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*int k = 0;
	char op = '+';
	Stack<int> a;
	int i = 0;
	while (toString(k) != "") {
		
		if(i < 2)cin >> k;
		else {
			cin >> op;
			
			switch (op) {
			case '+':
				cout << a.pop() + a.pop();
				break;
			case '-':
				cout << a.pop() - a.pop();
				break;
			case '/':
				cout << a.pop() / a.pop();
				break;
			case '*':
				cout << a.pop() * a.pop();
				break;
			}
			
			break;
		}
		if (k != 0) a.push(k);
		else break;

		i++;
	}*/
	double_linked_list<int> a;
	a.push_front(1);
	a.push_front(2);
	a.push_front(3);
	
	cout << a.pop_back() << endl;
	cout << a.pop_back() << endl;
	cout << a.pop_back() << endl;

}