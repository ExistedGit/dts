#pragma once
#include "dts.h"
//#include <map> // для ассоциативного массива символов в toString()
#include "map.h" // Переиграл и уничтожил
#include <cassert>
namespace dts {
	// Строка
	class String
	{
	private:
		friend ostream& operator<<(ostream& os, const String& s);
		friend istream& operator>>(istream& is, String& s);
		friend String operator+(const String& s1, const String& s2);
		friend String operator+(const String& s, int n);

		friend String& operator+=(String& s1, const String& s2);
		friend String& operator+=(String& s, int n);

		friend bool operator==(const String& s, const String& cs);
		friend bool operator!=(const String& s, const String& cs);

		friend bool operator<(const String& left, const String& right);
		friend bool operator>(const String& left, const String& right);

	protected:
		char* cstr;
		int _size;
		int _capacity;

		void adjustCapacity(int newCap);
	public:
		const char* c_str();

		operator string() const {
			return string(cstr);
		}


		String();
		explicit String(int size);
		String(const String& s);
		String(const char* cs);
		String(const char c);
		~String();
		String& operator=(const String& s) {
			
			delete[]cstr;
			cstr = nullptr;

			cstr = new char[s._capacity];
			strcpy(cstr, s.cstr);
			_capacity = s._capacity;
			_size = s._size;
			return *this;
		}

		int size() const;
		int length() const;
		String& append(const String& s);

		String& reverse();

		char& at(int index);
		char& operator[](int index) {
			return at(index);
		}
		char _at(int index) const {
			assert(index >= 0 && index <= _size+1 && "Строка: неверно указан индекс(_at)");
			
			return cstr[index];
		};
		friend class StringBuilder;
	};

	inline String toString(int n) {
		String result = "";
		if (n == 0) result.append("0");
		Map<int, char> digitChar = { { 0, '0' },{ 1, '1' },{ 2, '2' },{ 3, '3' },{ 4, '4' },{ 5, '5' },{ 6, '6' },{ 7, '7' },{ 8, '8' },{ 9, '9' } };

		while (n > 0) {
			result.append(digitChar[n % 10]);
			n /= 10;
		}

		return result.reverse();
	}

	// операторы для Строки
	inline ostream& operator<<(ostream& os, const String& s)
	{
		os << s.cstr;
		return os;
	}
	inline istream& operator>>(istream& is, String& s)
	{
		if (s.cstr != nullptr) {
			delete[]s.cstr;
			s.cstr = nullptr;
		}
		char buff[500];

		cin.getline(buff, 500);
		buff[499] = '\0';
		s.cstr = new char[strlen(buff) + 1];
		strcpy(s.cstr, buff);
		s._size = strlen(buff);
		return is;
	}

	inline String operator+(const String& s1, const String& s2)
	{
		String result = s1;
		result.append(s2);
		return result;
	}
	inline String operator+(const String& s, int n)
	{
		String result = s;
		result.append(toString(n));
		return result;
	}

	inline String& operator+=(String& s1, const String& s2)
	{
		return s1.append(s2);
	}
	inline String& operator+=(String& s, int n)
	{
		return s.append(toString(n));
	}

	inline bool operator>(const String& left, const String& right) {
		return strcmp(left.cstr, right.cstr) < 0;
	}
	inline bool operator<(const String& left, const String& right) {
		return strcmp(left.cstr, right.cstr) > 0;
	}

	inline bool operator>=(const String & left, const String & right) {
		if (left == right) return true;
		if (left > right) return true;
		return false;
	}

	inline bool operator==(const String& s, const String& cs) {
		return strcmp(s.cstr, cs.cstr) == 0;
	}
	inline bool operator!=(const String& s, const String& cs) {
		return strcmp(s.cstr, cs.cstr) != 0;
	}

	class StringBuilder {
	private:
		char** s;
		int _size;
		int _capacity;

		void nullArr();
		void checkCapacity(int c);
	public:

		StringBuilder(int capacity = 8);
		StringBuilder(String str, int capacity = 8);
		~StringBuilder();
		StringBuilder(const StringBuilder& orig);

		String toString() const;


		void setCapacity(unsigned int capacity);

		int getCapacity();

		void append(const String& str, bool endline = false);
		void appendLine(const String& str);

		void clear();
		StringBuilder& operator=(const StringBuilder& orig) {
			_capacity = orig._capacity;
			s = new char* [orig._capacity];
			_size = orig._size;
			for (int i = 0; i < orig._size; i++) {
				s[i] = new char[strlen(orig.s[i]) + 1];
				strcpy(s[i], orig.s[i]);
			}
		}

		StringBuilder& operator+=(const String& str) {
			append(str);
			return *this;
		}

		StringBuilder operator+(const String& str) {
			StringBuilder result = *this;
			result.append(str);
			return result;
		}
	};

	inline ostream& operator<<(ostream& os, const StringBuilder& str) {
		os << str.toString();
		return os;
	}
}

inline void dts::String::adjustCapacity(int newCap) {
	
	if (_capacity == 0) _capacity = 1;
	int oldCapacity = _capacity;
	if (newCap <= _capacity / 2) {
		while (true) {
			if (_capacity / 2 >= newCap)_capacity /= 2;
			else break;
		}
	}
	else if(newCap > _capacity){
		while (newCap > _capacity) _capacity *= 2;
	}
	if (_capacity == oldCapacity) return;
	

	char* oldArr = cstr;
	cstr = new char[_capacity];
	strcpy(cstr, oldArr);

	delete[]oldArr;
	oldArr = nullptr;
	
}

inline const char* dts::String::c_str() {
	return cstr;
}

inline dts::String::String() {
	_capacity = 4;
	_size = 0;
	cstr = new char[_capacity];
	cstr[0] = '\0';
}


inline dts::String::String(int size) : String() {
	adjustCapacity(size);
	cstr[0] = '\0'; // для strcat-совместимости
	_size = size;
}

inline dts::String::String(const String& s) {
	
	
	cstr = new char[s._capacity];
    strcpy(cstr, s.cstr);
	
	_capacity = s._capacity;
	_size = s._size;
}

inline dts::String::String(const char* cs) : String() {
	
	if (cs != nullptr) {
		adjustCapacity(strLen(cs)+1);
		strcpy(cstr, cs);
		_size = strLen(cs);
	}
}

inline dts::String::String(const char c) {
	cstr = new char[2];

	cstr[0] = c;
	cstr[1] = '\0';
	_size = 1;
	_capacity = 2;
}

inline dts::String::~String() {
	if (cstr != nullptr) {
		delete cstr;
		cstr = nullptr;
		_size = 0;
		_capacity = 0;
	}
}

inline int dts::String::size() const {
	return _size;
}

inline int dts::String::length() const {
	return _size;
}

inline dts::String& dts::String::append(const String& s) {
	adjustCapacity(_size + s._size + 1);
	strcat(cstr, s.cstr);
	_size = _size + s._size;
	return *this;
}

inline dts::String& dts::String::reverse() {
	int start = 0, end = _size - 1;
	while (start < end)
	{
		char temp = cstr[start];
		cstr[start] = cstr[end];
		cstr[end] = temp;
		start++;
		end--;
	}
	return *this;
}

inline char& dts::String::at(int index) {
	try {
		if (index >= 0 && index <= _size) {
			return cstr[index];
		}
		else throw out_of_range("Неверный индекс символа в строке");
	}
	catch (out_of_range err) {
		cerr << err.what();
	}
}

inline void dts::StringBuilder::nullArr() {
	for (int i = 0; i < _capacity; i++) {
		s[i] = nullptr;
	}
}

inline void dts::StringBuilder::checkCapacity(int c) {
	if (c > _capacity) {
		_capacity *= 2;
		char** newS = new char* [_capacity];
		for (int i = 0; i < _size; i++) {
			newS[i] = s[i];
		}
		delete s;
		s = newS;
	}
}

inline dts::StringBuilder::StringBuilder(int capacity) {
	if (capacity == 0) capacity = 8;

	_capacity = capacity;
	s = new char* [_capacity];
	nullArr();
	_size = 0;
}

inline dts::StringBuilder::StringBuilder(String str, int capacity) {
	if (capacity == 0) capacity = 8;
	_capacity = capacity;
	s = new char* [capacity];
	nullArr();
	s[0] = new char[str.size() + 1];
	strcpy(s[0], str.cstr);
	_size = 1;
}

inline dts::StringBuilder::~StringBuilder() {
	clear();
}

inline dts::StringBuilder::StringBuilder(const StringBuilder& orig) {
	_capacity = orig._capacity;
	s = new char* [orig._capacity];
	_size = orig._size;
	for (int i = 0; i < orig._size; i++) {
		s[i] = new char[strlen(orig.s[i]) + 1];
		strcpy(s[i], orig.s[i]);
	}
}

inline dts::String dts::StringBuilder::toString() const {
	if (s == nullptr) return "";
	int resultSize = 1;
	for (int i = 0; i < _size; i++) {
		resultSize += strlen(s[i]);
	}
	String result(resultSize);
	for (int i = 0; i < _size; i++) {
		strcat(result.cstr, s[i]);
	}
	return result;
}

inline void dts::StringBuilder::setCapacity(unsigned int capacity) {
	if (capacity < _size) return;

	_capacity = capacity;
	char** newS = new char* [_capacity];

	for (int i = 0; i < _capacity; i++) {
		newS[i] = nullptr;
	}

	for (int i = 0; i < _size; i++) {
		newS[i] = s[i];
	}
	delete s;
	s = newS;
}

inline int dts::StringBuilder::getCapacity() {
	return _capacity;
}

inline void dts::StringBuilder::append(const String& str, bool endline) {
	checkCapacity(_size + 1);
	s[_size] = new char[str.size() + 1 + endline];
	strcpy(s[_size], str.cstr);
	//cout << s[_size];
	if (endline) {
		s[_size][str.size()] = '\n';
		s[_size][str.size() + 1] = '\0';
	};
	_size++;
}

inline void dts::StringBuilder::appendLine(const String& str) {
	append(str, true);
}

inline void dts::StringBuilder::clear() {
	for (int i = 0; i < _size; i++) {
		delete s[i];
	}
	delete s;
	s = nullptr;
	_size = 0;
	_capacity = 0;
}


// Перевод числа в строку
