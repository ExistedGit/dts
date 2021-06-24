
#pragma once
#include <Windows.h>
#include "dts.h"
#include "htam.h"
using namespace htam;
using namespace std;
using namespace dts;

class Car {
	String number;
public:
	Car(String _number) {
		number = _number;
	}
	Car(const Car& orig) {
		number = orig.number;
	}
	Car& operator=(const Car& orig) {
		number = orig.number;
		return *this;
	}
};

String generateRandomString(unsigned int characters = 1) {
	std::random_device rd;
	std::mt19937 mt(rd());
	uniform_int_distribution<int> distribution(0, 4);
}

int main() {
	setlocale(LC_ALL, "");
	/*SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/
	cout.setf(ios::boolalpha);
	
	Stack<Car> parking;
	
	
}