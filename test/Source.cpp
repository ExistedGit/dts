
#include "dts.h"
using namespace std;
using namespace dts;

int main() {
	/*int k = 0;
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

	}*/

	linked_list<int> a;
	for (int i = 0; i < 5; i++) {
		int b;
		cin >> b;
		a.push_back(b);
	}
	a.print();
	int c;
	cin >> c;
	a.pop(c);
	a.print();
	

}