
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
	
	
	StringBuilder a = "������! "; // ���������������
	string b = "������������������... "; // ������
	String c = "������!"; // ������
	const char* d = " ��..."; // const char*

	cout << a + b + c + d;
}