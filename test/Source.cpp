
#pragma once
#include <Windows.h>
#include "dts.h"
#include "htam.h"
using namespace htam;
using namespace std;
using namespace dts;

int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout.setf(ios::boolalpha);
	
	
	linked_list<int> a = {3, 2, 1, 5, 4};
	int index;
	cout << a << endl;
	cout << "Index: ";
	cin >> index;
	cout << "a[" << index << "] = " << a[index]<<endl;
}