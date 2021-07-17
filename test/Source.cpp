
#pragma once
#include <Windows.h>
#include <vector>
#include <sstream>
#include <map>
#include "dts.h"
#include "vector.h"
#include "list.h"
#include "dtstring.h"
#include "map.h"
#include "htam.h"
#include <list>
using namespace htam;
using namespace std;
using namespace dts;

#define pause system("pause")
#define cls system("cls");


class BaseUnit {
protected:
	int hp;
	int minAtc;
	int maxAtc;

	string name;
public:


	virtual int attack() const
	{
		return rand() % (abs(minAtc) + abs(maxAtc));
	}
	virtual bool hurt(int atc)
	{
		hp -= atc;
		return hp < 0;
	}
	const string& getName() const {
		return name;
	};
};

enum Difficulty {
	EASY = 3,
	MIDDLE = 6,
	HARD = 9
};

namespace Dire {
	class DireUnit : public BaseUnit {};

	class Ghoul : virtual DireUnit {
	public:
		Ghoul() {
			hp = 100;
			minAtc = 10;
			maxAtc = 15;
			name = "Ghoul";
		}

	};

	class CryptFiend : virtual DireUnit {
	public:
	public:
		CryptFiend() {
			hp = 150;
			maxAtc = 20;
			minAtc = 10;
			name = "Crypt Fiend";
		}
	};
	
	class Abomination : virtual DireUnit {
	public:
		Abomination() {
			hp = 300;
			minAtc = 20;
			maxAtc = 30;
			name = "Abomination";
		}
	};

	class Necromancer :virtual DireUnit {

	public:
		Necromancer() {
			hp = 200;
			maxAtc = 50;
			minAtc = 45;
			name = "Necromancer";
		}
		
	};

	class Lich : virtual DireUnit {
	public:
		Lich() {
			hp = 500;
			maxAtc = 80;
			minAtc = 75;
			name = "Lich";
		}
	};

	class DreadLord : virtual DireUnit {
	public:
		DreadLord() {
			hp = 600;
			maxAtc = 85;
			minAtc = 90;
			name = "Dread Lord";
		}
		
	};

	void createDireTeam(Deque<BaseUnit*>& d, Difficulty diff) {
		const vector<DireUnit*> heroes = { (DireUnit*)(new Lich()), (DireUnit*)(new DreadLord()) };
		const vector<DireUnit*> mediumUnits = { (DireUnit*)(new Abomination()), (DireUnit*)(new Dire::Necromancer()) };
		const vector<DireUnit*> weakUnits = { (DireUnit*)(new Ghoul()), (DireUnit*)(new CryptFiend()) };
		
		
		
		for (int i = 0; i < diff/3-1; i++) {
			d.push_front((BaseUnit*)heroes[rand()%2]);
		}

		for (int i = 0; i < diff / 2; i++) {
			d.push_front((BaseUnit*)mediumUnits[rand() % 2]);
		}

		for (int i = 0; i < diff - diff/3 + 1 - diff / 2; i++) {
			d.push_front((BaseUnit*)weakUnits[rand() % 2]);
		}
	}
}

namespace Radiant {
	class RadiantUnit : public BaseUnit {};

	class Rifleman : virtual RadiantUnit {
	public:
		Rifleman() {
			hp = 100;
			minAtc = 12;
			maxAtc = 17;
			name = "Rifleman";
		}
	};

	class Knight : virtual RadiantUnit {
	public:
		Knight() {
			hp = 150;
			minAtc = 10;
			maxAtc = 12;
			name = "Knight";
		}
	};

	class Priest : virtual RadiantUnit {
	public:
		Priest() {
			hp = 175;
			minAtc = 18;
			maxAtc = 23;
			name = "Priest";
		}
	};
	class SpellBreaker : virtual RadiantUnit {
	public:
		SpellBreaker() {
			hp = 275;
			minAtc = 15;
			maxAtc = 20;
			name = "Spell Breaker";
		}
	};

	class Paladin : virtual RadiantUnit {
	public:
		Paladin() {
			hp = 750;
			minAtc = 70;
			maxAtc = 80;
			name = "Paladin";
		}
	};

	class Archmage : virtual RadiantUnit {
	public:
		Archmage() {
			hp = 550;
			minAtc = 85;
			maxAtc = 90;
			name = "Archmage";
		}
	};

	void createRadiantTeam(Deque<BaseUnit*>& d, Difficulty diff) {
		const vector<RadiantUnit*> heroes = { (RadiantUnit*)(new Rifleman()), (RadiantUnit*)(new Knight()) };
		const vector<RadiantUnit*> mediumUnits = { (RadiantUnit*)(new SpellBreaker()), (RadiantUnit*)(new Priest()) };
		const vector<RadiantUnit*> weakUnits = { (RadiantUnit*)(new Paladin()), (RadiantUnit*)(new Archmage()) };



		for (int i = 0; i < diff / 3 - 1; i++) {
			d.push_front((BaseUnit*)heroes[rand() % 2]);
		}

		for (int i = 0; i < diff / 2; i++) {
			d.push_front((BaseUnit*)mediumUnits[rand() % 2]);
		}

		for (int i = 0; i < diff - diff / 3 + 1 - diff / 2; i++) {
			d.push_front((BaseUnit*)weakUnits[rand() % 2]);
		}
	}
};

class ByteString : public dts::String {
public:

	ByteString() {
		_capacity = 4;
		_size = 0;
		cstr = new char[_capacity];
		cstr[0] = '\0';
	}
	ByteString(const char* cs) {
		int i;
		adjustCapacity(strlen(cs)+2);
		cstr[0] = '0'; // Знак числа
		for (i = 0; cs[i+1] != '\0'; i++) {
			if (cs[i] != '0' && cs[i] != '1') {
				delete cstr;
				cstr = new char[1];
				cstr[0] = '\0';
				_size = 0;
				_capacity = 1;
				return;
			}
			cstr[i+1] = cs[i];
		}
		cstr[i+1] = cs[i];
		cstr[i+2] = '\0';
		_size = strlen(cs)+1;
	};
	ByteString(const char c) {
		if (c == '0' || c == '1') {
			cstr = new char[4];
			cstr[0] = '0'; // Знак числа
			cstr[1] = c;
			cstr[2] = '\0';
			_size = 2;
			_capacity = 4;
		}
		else {
			cstr = new char[1];
			cstr[0] = '\0';
			_size = 0;
			_capacity = 1;
		}
	}

	explicit ByteString(int size) {
		adjustCapacity(size);
		cstr[0] = '\0'; // для strcat-совместимости
		_size = size;
	}

	ByteString& operator=(const ByteString& s) {

		delete[]cstr;
		cstr = nullptr;

		cstr = new char[s._capacity];
		strcpy(cstr, s.cstr);
		_capacity = s._capacity;
		_size = s._size;
		return *this;
	}


	ByteString& append(const ByteString& bs) {
		adjustCapacity(_size + bs._size + 1);
		strcat(cstr, bs.cstr+!(bs._at(0) == '\0'));
		_size = _size + bs._size;
		return *this;
	}
	void changeSign(bool positive = true) {
		cstr[0] = (positive ? '0' : '1');
		
	}

private:

	friend ostream& operator<<(ostream& os, const ByteString& s);
	friend ByteString operator+(const ByteString& s1, const ByteString& s2);

	friend ByteString& operator+=(ByteString& s1, const ByteString& s2);

	friend bool operator==(const ByteString& s, const ByteString& cs);
	friend bool operator!=(const ByteString& s, const ByteString& cs);

	friend bool operator<(const ByteString& left, const ByteString& right);
	friend bool operator>(const ByteString& left, const ByteString& right);

};

#pragma region Операторы

ostream& operator<<(ostream& os, const ByteString& s)
{
	cout << s.cstr;
	return os;
}
ByteString operator+(const ByteString& s1, const ByteString& s2)
{
	ByteString result(s1);
	result.append(s2);
	return result;
}


ByteString& operator+=(ByteString& s1, const ByteString& s2)
{
	return s1.append(s2);
}


bool operator==(const ByteString& s, const ByteString& cs)
{
	return strcmp(s.cstr, cs.cstr) == 0;
}

bool operator!=(const ByteString& s, const ByteString& cs)
{
	return strcmp(s.cstr, cs.cstr) != 0;
}

bool operator<(const ByteString& left, const ByteString& right)
{
	if (left.cstr[0] != right.cstr[0]) {
		return left.cstr[0] == '1' && right.cstr[0] == '0';
	}
	return strcmp(left.cstr, right.cstr) == -1;
}
bool operator>(const ByteString& left, const ByteString& right)
{
	if (left.cstr[0] != right.cstr[0]) {
		return left.cstr[0] == '0' && right.cstr[0] == '1';
	}
	return strcmp(left.cstr, right.cstr) == 1;
}
#pragma endregion
int main() {
	srand(time(0));
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	// Зачем нужен такой класс? Неизвестно
	ByteString a("111");
	a.changeSign(0);
	a.append("0143");
	cout << a << endl;
	
	ByteString b("01a1");
	cout << b << endl;
}
