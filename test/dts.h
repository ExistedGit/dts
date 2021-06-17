#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <mutex> // для инициализации вектора списком
#include <map> // для ассоциативного массива символов в toString()
using namespace std;

namespace dts {
	// Связанный список
	template <typename T>
	class linked_list {
	private:

		class LinkedElement {
		public:
			LinkedElement* next;
			T value;

			LinkedElement() {
				next = nullptr;
			}

			~LinkedElement() {
				next = nullptr;
			}
		};

		LinkedElement* _first;
		int _size;

		void recursivePrint(LinkedElement* l = nullptr) { // Рекурсивная начинка вывода списка
			if (l == nullptr) {
				cout << _first->value << " ";
				l = _first;
				return recursivePrint(l);
			}

			if (l->next != nullptr) {
				l = l->next;
				cout << l->value << " ";
				return recursivePrint(l);
			}
			else {
				cout << endl;
				return;
			}
		}

		void addElemR(const T elem, LinkedElement* linkedElem = nullptr) { // Рекурсивная начинка добавления объекта в список
			if (_first == nullptr) {
				_first = new LinkedElement();
				_first->value = elem;
				_size++;
				return;
			}

			if (linkedElem == nullptr) linkedElem = _first;


			if (linkedElem->next == nullptr)
			{
				linkedElem->next = new LinkedElement();
				linkedElem->next->value = elem;

				_size++;
				return;
			}

			linkedElem = linkedElem->next;


			return addElemR(elem, linkedElem);
		}

		T& getElemR(int index, int current = 0, LinkedElement* linkedElem = nullptr) { // Рекурсивная начинка нахождения n-ного объекта списка
			if (index < 0 || index >= _size) return _first->value;

			if (linkedElem == nullptr) linkedElem = _first;

			if (index != current) {
				linkedElem = linkedElem->next;
				current++;
				return getElemR(index, current, linkedElem);
			}
			else return linkedElem->value;
		}

		T& pop_backR(LinkedElement* linkedElem = nullptr) { // Рекурсивная начинка удаления последнего объекта списка
			if (linkedElem == nullptr) linkedElem = _first;
			if (linkedElem->next == nullptr) {
				T value = linkedElem->value;
				linkedElem = nullptr;
				return value;
			}
			else if (linkedElem->next->next == nullptr) {
				T value = linkedElem->next->value;
				delete linkedElem->next;
				linkedElem->next = nullptr;
				_size--;
				return value;
			}
			else {
				linkedElem = linkedElem->next;
				return pop_backR(linkedElem);
			}
		}

		void bubbleSortCycleR(LinkedElement* linkedElem = nullptr) { // Метод, проводящий один цикл пузырьковой сортировки(повторяется нужное количество раз уже в bubbleSort()
			if (linkedElem == nullptr) linkedElem = _first; // первый рассматриваемый элемент будет первым в списке

			if (linkedElem->next != nullptr) { // Если есть следующий элемент, то...
				if (linkedElem->value >= linkedElem->next->value) // ...если его значение больше значения текущего элемента,..
				{
					swap(linkedElem->value, linkedElem->next->value); // ...меняем их местам, после чего...
					linkedElem = linkedElem->next; // переставляем текущий элемент на следующий в списке,..

				}
				// Если элемент не больше следующего, переходим далее
				else { //.., иначе...
					linkedElem = linkedElem->next; // ...тоже переставляем текущий элемент на следующий и...
					return bubbleSortCycleR(linkedElem); // ...повторяем операцию.
				}
			}
			// Если текущий элемент конечный в списке
			else return; // .., иначе завершаем цикл.

			return bubbleSortCycleR(linkedElem); // Повторяем операцию до конца списка
		}

		T popR(int index, LinkedElement* linkedElem = nullptr, int current = 0) {
			
			if (linkedElem == nullptr) {
				if (index == current) {
					T value = _first->value;
					LinkedElement* tmp = _first;
					
					_first = _first->next;
					delete tmp;
					return value;
				}
				linkedElem = _first;
			}
			if (index != current +1) {
				linkedElem = linkedElem->next;
				current++;
				return popR(index, linkedElem, current);
			}
			else {
				T value = linkedElem->next->value;
				LinkedElement* tmp = linkedElem->next;
				
				linkedElem->next = linkedElem->next->next;
				delete tmp;
				return value;
			}
		}

	public:
		linked_list() {
			_first = nullptr;
			_size = 0;
		}

		// Процедурные оболочки рекурсивных функций
		linked_list* push_back(const T elem) {
			addElemR(elem);
			return this;
		}

		T pop_front() {
			LinkedElement* tmp = _first;
			T value = tmp->value;
			if (_first->next != nullptr) {
				_first = _first->next;
			}
			else _first = nullptr;
			
			delete tmp;
			_size--;
			return value;
		}
		T pop_back() {			
			
			return pop_backR();
		}

		T pop(int index) {
			return popR(index);
		}

		void print() {
			recursivePrint();
		}

		T& first() {
			return _first->value;
		}
		T& last() {
			return (*this)[_size - 1];
		}



		T& operator[](int index) {
			return getElemR(index);
		}

		linked_list* bubbleSort() {
			
			for (int i = 0; i < _size; i++) {
				bubbleSortCycleR();
			}
			return this;
		}
	};

	// Вектор(динамический массив)
	template <typename Type>
	class Vector
	{
	private:
		Type* arr;
		int _size;
	public:
		Vector() {
			arr = nullptr;
			_size = 0;
		}
		Vector(const Vector& orig) {
			_size = orig._size;
			arr = new Type[orig._size];
			for (int i = 0; i < _size; i++) {
				arr[i] = orig.arr[i];
			}
		}
		Vector(std::initializer_list<Type> _arr) {
			_size = _arr._size();

			arr = new Type[_size];
			for (int i = 0; i < _size; i++) {
				arr[i] = *(_arr.begin() + i);
			}
		}
		void operator=(std::initializer_list<Type> _arr) {

			if (arr != nullptr) {
				delete[]arr;
				arr = nullptr;
			}
			_size = _arr._size();

			arr = new Type[_size];
			for (int i = 0; i < _size; i++) {
				arr[i] = *(_arr.begin() + i);
			}
		}
		void operator=(std::nullptr_t nptr) {
			if (arr != nullptr) {
				delete[]arr;
				arr = nullptr;
			}
			arr = nullptr;
			_size = 0;
		}
		~Vector() {
			if (arr != nullptr) {
				delete[]arr;
				arr = nullptr;
			}
			_size = 0;
		}

		void operator=(const Vector<Type>& orig) {
			if (arr != nullptr) {
				delete[]arr;
				arr = nullptr;
			}
			if (!orig.empty()) {
				_size = orig._size;
				arr = new Type[_size];
				for (int i = 0; i < _size; i++) {
					arr[i] = orig.arr[i];
				}
			}
			else {
				_size = 0;
				arr = nullptr;
			}
		}

		void push_back(const Type& elem) {

			Type* p = new Type[_size + 1];
			int shift = 0;
			for (size_t i = 0; i < _size; i++)
			{
				p[i] = arr[i - shift];
			}
			p[_size] = elem;
			if (arr != nullptr) delete[]arr;
			_size++;
			arr = p;
		}

		int size() const {
			return _size;
		}

		bool empty() const {
			return _size == 0;
		}

		Type& at(int index) {
			if (index >= 0 && index < _size) return arr[index];
		}

		Type& operator[](int index) {
			if (index >= 0 && index < _size) return arr[index];
		}

		bool remove(int index = -1) {
			if (index >= 0 && index < _size) {
				if (index == -1) index = _size - 1;

				Type* p = new Type[_size - 1];
				for (int i = 0; i < index; i++) {
					p[i] = arr[i];
				}
				for (int i = index + 1; i < _size; i++) {
					p[i - 1] = arr[i];
				}
				delete[]arr;
				_size--;
				arr = p;

				return true;
			}
			else return false;
		}

		void print() const {
			for (int i = 0; i < _size; i++) {
				std::cout << arr[i] << " ";
			}
		}

	};


	inline int strLen(const char* s) {
		int size = 0;
		for (int i = 0; s[i] != '\0'; i++) {
			size++;
		}
		return size;
	}

	// Строка
	class String
	{
	private:
		char* cstr;
		int _size;
	public:
		char* c_str() {
			return cstr;
		}

		String() {
			cstr = nullptr;
			_size = 0;
		}
		explicit String(int size) {
			cstr = new char[size];
			_size = size;
		}
		String(const String& s) {
			if (s.cstr != nullptr) {
				cstr = new char[strLen(s.cstr) + 1];
				strcpy(cstr, s.cstr);
			}
			else cstr = nullptr;

			_size = s._size;
		}
		String(const char* cs) {
			if (cs != nullptr) {
				cstr = new char[strLen(cs) + 1];
				strcpy(cstr, cs);
				_size = strLen(cs);
			}
			else {
				cstr = nullptr;
				_size = strLen(cs);
			}

		}
		~String() {
			delete[]cstr;
			cstr = nullptr;
			_size = 0;
		}
		void operator=(const String& s) {
			if (s.cstr != nullptr) {
				cstr = new char[strLen(s.cstr) + 1];
				strcpy(cstr, s.cstr);
			}
			else cstr = nullptr;
			_size = s._size;
		}
		void operator=(const char* cs) {
			if (cs != nullptr) {
				cstr = new char[strLen(cs) + 1];
				strcpy(cstr, cs);
			}
			else cstr = nullptr;
			_size = strLen(cs);
		}

		int size() {
			return _size;
		}
		int length() {
			return _size;
		}
		String& append(const String& s) {
			char* newCStr = new char[_size + s._size + 1];
			strcpy(newCStr, cstr);
			strcat(newCStr, s.cstr);

			if (cstr != nullptr) {
				delete[]cstr;
				cstr = nullptr;
			}
			cstr = newCStr;
			_size = _size + s._size;
			return *this;
		}
		String& append(const char* s) {
			char* newCStr = new char[_size + strLen(s) + 1];
			strcpy(newCStr, cstr);
			strcat(newCStr, s);

			if (cstr != nullptr) {
				delete[]cstr;
				cstr = nullptr;
			}
			cstr = newCStr;
			_size = _size + strLen(s);
			return *this;
		}
		String& append(char s) {
			char* newCStr = new char[_size + 2];
			strcpy(newCStr, cstr);
			newCStr[_size] = s;
			newCStr[_size + 1] = '\0';
			if (cstr != nullptr) {
				delete[]cstr;
				cstr = nullptr;
			}
			cstr = newCStr;
			_size++;
			return *this;
		}

		String& reverse() {
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

		friend ostream& operator<<(ostream& os, const String& s);
		friend istream& operator>>(istream& is, String& s);
		friend String operator+(const String& s1, const String& s2);
		friend String operator+(const String& s, const char* cs);
		friend String operator+(const String& s, int n);
		friend bool operator==(const String& s, const char* cs);
		friend bool operator!=(const String& s, const char* cs);
	};

	// Перевод числа в строку
	inline String toString(int n) {



		String result = "";
		if (n == 0) result.append("0");

		map<int, char> digitChar = { { 0, '0' },{ 1, '1' },{ 2, '2' },{ 3, '3' },{ 4, '4' },{ 5, '5' },{ 6, '6' },{ 7, '7' },{ 8, '9' },{ 9, '9' } };

		

		while (n > 0) {
			result.append(digitChar[n % 10]);
			n /= 10;
		}

		return result.reverse();
	}

	// операторы для Строки
	ostream& operator<<(ostream& os, const String& s)
	{
		os << s.cstr;
		return os;
	}
	istream& operator>>(istream& is, String& s)
	{
		is >> s.cstr;
		return is;
	}

	String operator+(const String& s1, const String& s2)
	{
		String result = s1;
		result.append(s2);
		return result;
	}

	String operator+(const String& s, const char* cs)
	{
		String result = s;
		result.append(cs);
		return result;
	}

	String operator+(const String& s, int n)
	{
		String result = s;
		result.append(toString(n));
		return result;
	}


	bool operator==(const String& s, const char* cs) {
		return _stricmp(s.cstr, cs) == 0;
	}
	bool operator!=(const String& s, const char* cs) {
		return _stricmp(s.cstr, cs) != 0;
	}
}



