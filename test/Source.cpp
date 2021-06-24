
#pragma once
#include <Windows.h>
#include "dts.h"
#include "htam.h"
using namespace htam;
using namespace std;
using namespace dts;

enum randomStringMode {
	LETTERS,
	NUMBERS,
	MIXED
};

String generateRandomString(unsigned int characters = 1, bool ru = false, randomStringMode mode = MIXED) {
	String result;


	std::random_device rd;
	std::mt19937 mt(rd());
	if (ru) {
		uniform_int_distribution<int> letters((unsigned char)'А', (unsigned char)'Я');
		uniform_int_distribution<int> numbers(48, 57);
		
		uniform_int_distribution<int> ifLetters(0, 1);

		for (int i = 0; i < characters; i++) {
			switch (mode) {
			case LETTERS:
				result.append(letters(mt));
				break;
			case NUMBERS:
				result.append(numbers(mt));
				break;
			case MIXED:
				if (ifLetters(mt)) {
					result.append(letters(mt));
				}
				else {
					result.append(numbers(mt));
				}
				break;
			}
			
		}
	}
	else {
		uniform_int_distribution<int> letters(65, 90);
		uniform_int_distribution<int> numbers(48, 57);
		uniform_int_distribution<int> ifLetters(0, 1);
		for (int i = 0; i < characters; i++) {
			switch (mode) {
			case LETTERS:
				result.append(letters(mt));
				break;
			case NUMBERS:
				result.append(numbers(mt));
				break;
			case MIXED:
				if (ifLetters(mt)) {
					result.append(letters(mt));
				}
				else {
					result.append(numbers(mt));
				}
				break;
			}
		}
	}
	return result;
}

String generateCarNumberUA() {
	String result;
	vector<String> prefixes = {"AA", "AI", "AC", "BK", "AM", "BI", "BM", "AX", "BB", "AH", "AP", "BT", "AK", "CH", "BE", "BH", "AB", "BX", "CE", "AT", "AO", "BC", "BO", "AE", "BBA", "CA", ""};

	std::random_device rd;
	std::mt19937 mt(rd());
	uniform_int_distribution<int> numbers(0, prefixes.size()-1);
	result += prefixes[numbers(mt)];
	result += generateRandomString(4, true, NUMBERS);
	result += generateRandomString(2, false, LETTERS);
	return result;
}
class Car {

public:
	String number;
	Car() {
		number = generateRandomString(8);
	}
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


enum PlateColor {
	Red, Green, Blue
};
class Plate {
public:

	PlateColor color;
	Plate(PlateColor _color = Red) {
		color = _color;
	}
	bool operator==(const Plate& right) {
		
		return color == right.color;
	}
};

int main() {
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout.setf(ios::boolalpha);
	
	unsigned int pileSize;
	Stack<Plate> pile;
	cout << "Введите количество тарелок: ";
	cin >> pileSize;
	
	PlateColor color = pile.pop().color;

	int count = 0;
	int pairIndex = -1;
	for (int i = 0; i < pileSize; i++) {
		if (pile.pop() == Plate(color)) {
			count++;
			if (count == 2) {
				pairIndex = i;
			}
		}
	}
	cout << endl;


	//Stack<Car> parking;
	//for (int i = 0; i < 8; i++) {
	//	Car c = Car(generateCarNumberUA());
	//	parking.push(c);
	//	cout << c.number << " ";
	//}
	//cout << endl;
	//for (int i = 0; i < 8; i++) {
	//	cout << parking.pop().number << " ";
	//}
}