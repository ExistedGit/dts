
#include "dts.h"
#include <Windows.h>
using namespace std;
using namespace dts;

int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int k = 0;
	char op = '+';
	linked_list<int> a;
	int i = 0;
	while (toString(k) != "") {
		
		if(i < 2)cin >> k;
		else {
			cin >> op;
			
			switch (op) {
			case '+':
				cout << a.pop_front() + a.pop_front();
				break;
			case '-':
				cout << a.pop_front() - a.pop_front();
				break;
			case '/':
				cout << a.pop_front() / a.pop_front();
				break;
			case '*':
				cout << a.pop_front() * a.pop_front();
				break;
			}
			
			break;
		}
		if (k != 0) a.push_back(k);
		else break;

		i++;

	}
	
}