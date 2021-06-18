#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define RECURSIVE_LINKED_FUNCTIONS

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
			if (_first == nullptr) return;
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
		void addElemI(const T elem) { // Итеративная начинка добавления объекта в список
			if (_first == nullptr) {
				_first = new LinkedElement();
				_first->value = elem;
			}
			LinkedElement* linkedElem = _first;
			while (linkedElem->next != nullptr) {
				linkedElem = linkedElem->next;
			}
			linkedElem->next = new LinkedElement();
			linkedElem->next->value = elem;
		}
		T& getElemR(int index, int current = 0, LinkedElement* linkedElem = nullptr) { // Рекурсивная начинка нахождения n-ного объекта списка
			if (index < 0 || index >= _size) {
				throw "Неверный индекс связанного списка";
			};

			if (linkedElem == nullptr) linkedElem = _first;

			if (index != current) {
				linkedElem = linkedElem->next;
				current++;
				return getElemR(index, current, linkedElem);
			}
			else return linkedElem->value;
		}
		T& getElemI(int index) { // Итеративная начинка нахождения n-ного объекта списка
			LinkedElement* linkedElem = _first;
			for (int current = 0; current != index; current++) {
				linkedElem = linkedElem->next;
			}
			return linkedElem->value;
		}
		T& pop_backR(LinkedElement* linkedElem = nullptr) { // Рекурсивная начинка удаления последнего объекта списка
			if (linkedElem == nullptr) linkedElem = _first;
			if (linkedElem->next == nullptr) {
				T value = linkedElem->value;
				linkedElem = nullptr;
				_size--;
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
		T& pop_backI() { // Итеративная начинка удаления последнего объекта списка
			LinkedElement* linkedElem = _first;
			while (linkedElem->next->next != nullptr) {
				linkedElem = linkedElem->next;
			}
			T value = linkedElem->next->value;
			delete linkedElem->next;
			linkedElem->next = nullptr;
			return value;
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
		void bubbleSortI() { 
			LinkedElement linkedElem = _first;
			for (int i = 0; i < _size; i++) {
				if (linkedElem->value > linkedElem->next->value) {
					swap(linkedElem->value, linkedElem->next->value);
					
				}
				linkedElem = linkedElem->next;
			}
		}
		T popR(int index, LinkedElement* linkedElem = nullptr, int current = 0) {
			if (linkedElem == nullptr) {
				if (index == current) {
					T value = _first->value;
					LinkedElement* tmp = _first;
					
					_first = _first->next;
					delete tmp;
					_size--;
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

		
		T popR(int index) {
			LinkedElement* linkedElem = _first;
			for (int curr = 0; curr + 1 != index; curr++) {
				linkedElem = linkedElem->next;
			}
			T value = linkedElem->next->value;
			delete linkedElem->next;
			linkedElem->next = nullptr;
			return value;
		}
	public:
		linked_list() {
			_first = nullptr;
			_size = 0;
		}
		linked_list(const std::initializer_list<T> il) {
			for (int i = 0; i < il.size(); i++) {
				push_back(il[i]);
			}
		}
		~linked_list() {
			clear();
		}
		
		linked_list* clear() {
			while(_size != 0) pop_front();
			return this;
		}

		// Процедурные оболочки рекурсивных функций
		linked_list* push_back(const T elem) {
			addElemR(elem);
			return this;
		}

		linked_list* push_front(const T elem) {
			if (_first == nullptr) {
				_first = new LinkedElement();
				_first->value = elem;
				_size++;
			}
			else {
				LinkedElement* oldFirst = _first;
				_first = new LinkedElement();
				_first->next = oldFirst;
				_first->value = elem;
				_size++;
			}
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

		T& at(int index) {
			try {
				return getElemR(index);
			}
			catch (const char* msg) {
				cerr << msg << endl;
			}
		}

		T& operator[](int index) {
			return at(index);
			
		}

		int size() {
			return _size;
		}
		template<typename T>
		friend void bubbleSort(linked_list<T>& a);

		template<typename type>
		friend ostream& operator<<(ostream& os, linked_list<type>& a);
	};
	template<typename type>
	ostream& operator<<(ostream& os, linked_list<type>& a) {
		a.print();
		return os;
	}

	template <typename T>
	void bubbleSort(linked_list<T>& a) { // Работает только с численными списками
		string tID = typeid(T).name();
		if (tID == "int" || tID == "float" || tID == "double") {
			for (int i = 0; i < a._size; i++) {
				a.bubbleSortCycleR();
			}
		}
	}

	template <typename T>
	class double_linked_list {
	private:

		class dLinkedElement {
		public:
			dLinkedElement* next;
			dLinkedElement* prev;
			T value;

			dLinkedElement() {
				next = nullptr;
				prev = nullptr;
			}

			~dLinkedElement() {
				next = nullptr;
				prev = nullptr;
			}
		};

		dLinkedElement* _first;
		int _size;

		void recursivePrint(dLinkedElement* l = nullptr) { // Рекурсивная начинка вывода списка
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

		void addElemR(const T elem, dLinkedElement* linkedElem = nullptr) { // Рекурсивная начинка добавления объекта в список
			if (_first == nullptr) {
				_first = new dLinkedElement();
				_first->value = elem;
				_size++;
				return;
			}

			if (linkedElem == nullptr) linkedElem = _first;


			if (linkedElem->next == nullptr)
			{
				linkedElem->next = new dLinkedElement();
				linkedElem->next->value = elem;
				linkedElem->next->prev = linkedElem;

				_size++;
				return;
			}

			linkedElem = linkedElem->next;
			return addElemR(elem, linkedElem);
		}

		T& getElemR(int index, int current = 0, dLinkedElement* linkedElem = nullptr) { // Рекурсивная начинка нахождения n-ного объекта списка
			if (index < 0 || index >= _size) {
				throw invalid_argument("Неверный индекс связанного списка");
			};

			if (linkedElem == nullptr) linkedElem = _first;

			if (index != current) {
				linkedElem = linkedElem->next;
				current++;
				return getElemR(index, current, linkedElem);
			}
			else return linkedElem->value;
		}

		T& pop_backR(dLinkedElement* linkedElem = nullptr) { // Рекурсивная начинка удаления последнего объекта списка
			
			
			if (linkedElem == nullptr) {
				linkedElem = _first;
			}

			if (linkedElem->next == nullptr) {
				T value = linkedElem->value;
				dLinkedElement* nextPtr= linkedElem->prev;
				delete linkedElem;
				linkedElem = nullptr;
				if(nextPtr != nullptr) nextPtr->next = nullptr;
				_size--;
				return value;
			}	else {
				linkedElem = linkedElem->next;
				return pop_backR(linkedElem);
			}
		}

		void bubbleSortCycleR(dLinkedElement* linkedElem = nullptr) { // Метод, проводящий один цикл пузырьковой сортировки(повторяется нужное количество раз уже в bubbleSort()
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

		T popR(int index, dLinkedElement* linkedElem = nullptr, int current = 0) {

			if (linkedElem == nullptr) {
				if (index == current) {
					T value = _first->value;
					dLinkedElement* tmp = _first;

					_first = _first->next;
					delete tmp;
					_size--;
					return value;
				}
				linkedElem = _first;
			}
			if (index != current + 1) {
				linkedElem = linkedElem->next;
				current++;
				return popR(index, linkedElem, current);
			}
			else {
				T value = linkedElem->next->value;
				dLinkedElement* tmp = linkedElem->next;
				linkedElem->next = linkedElem->next->next;
				linkedElem->next->prev = linkedElem;
				delete tmp;
				return value;
			}
		}



	public:
		double_linked_list() {
			_first = nullptr;
			_size = 0;
		}
		~double_linked_list() {
			clear();
		}

		double_linked_list* clear() {
			while (_size != 0) pop_front();
			return this;
		}

		// Процедурные оболочки рекурсивных функций
		double_linked_list* push_back(const T elem) {
			addElemR(elem);
			return this;
		}

		double_linked_list* push_front(const T elem) {
			
			if (_first == nullptr) {
				_first = new dLinkedElement();
				_first->value = elem;
				_size++;
			}
			else {
				dLinkedElement* oldFirst = _first;
				_first = new dLinkedElement();
				_first->next = oldFirst;
				oldFirst->prev = _first;
				_first->value = elem;
				_size++;
			}
			return this;
		
		}
		T pop_front() {
			if (_size == 0) {
				throw runtime_error("Список пуст");
			}

			dLinkedElement* tmp = _first;
			T value = tmp->value;
			if (_first->next != nullptr) {
				_first = _first->next;
			}
			else _first = nullptr;

			_first->prev = nullptr;
			delete tmp;
			_size--;
			return value;
		}
		T pop_back() {
			if (_size == 0) {
				throw runtime_error("Список пуст");
			}
			return pop_backR();
		}

		T pop(int index) {
			if (index < 0 || index >= _size) {
				throw out_of_range("Неверный индекс");
			}
			return popR(index);
		}

		void print() {
			recursivePrint();
		}

		T& first() {
			if (_size == 0) {
				throw runtime_error("Список пуст");
			}
			return _first->value;
		}
		T& last() {
			if (_size == 0) {
				throw runtime_error("Список пуст");
			}
			return (*this)[_size - 1];
		}

		T& at(int index) {
			
			return getElemR(index);
			
		}

		T& operator[](int index) {
			return at(index);

		}

		int size() {
			return _size;
		}
	};
	template <typename T>
	class Deque {
	private:
		double_linked_list<T> deque;
	public:
		Deque* enqueueFirst(const T& elem) {
			deque.push_front(elem);
			return this;
		}
		Deque* enqueueLast(const T& elem) {
			deque.push_back(elem);
			return this;
		}

		T dequeueFirst() {
			return deque.pop_front();
			
		}
		T dequeueLast() {
			return deque.pop_back();
		}
		T& first() {
			return deque.first();
		}
		T& last() {
			return deque.last();
		}
		int count() {
			return deque.size();
		}
	};

	template <typename T>
	class Stack {
	private:
		Deque<T> stack;
	public:

		Stack* push(const T& elem) {
			stack.enqueueFirst(elem);
			return this;
		}
		T pop() {
			if (stack.count() == 0) {
				throw "Стек пуст!";
			}
			return stack.dequeueLast();
		}
		T peek() {
			if (stack.size() == 0) {
				throw "Стек пуст!";
			}
			return stack.last();
		}
		int count() {
			return stack.count();
		}

	};

	template <typename T>
	class Queue {
	private:
		Deque<T> queue;
	public:

		Queue* enqueue(const T& elem) {
			queue.enqueueLast(elem);
			return this;
		}
		T dequeue() {
			if (queue.size()  == 0) {
				throw "Стек пуст!";
			}
			return queue.dequeueFirst();
		}
		T peek() {
			if (queue.size() == 0) {
				throw "Стек пуст!";
			}
			return queue.first();
		}
		int count() {
			return queue.count();
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



