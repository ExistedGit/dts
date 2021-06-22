
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
	
	
	StringBuilder a = "Власть! "; // СтрокоСтроитель
	string b = "ААААААААБСОЛЮЮТНАЯ... "; // строка
	String c = "ВЛАСТЬ!"; // Строка
	const char* d = " Эх..."; // const char*

	cout << a + b + c + d;
}