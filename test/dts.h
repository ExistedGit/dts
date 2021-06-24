#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <mutex> // для инициализации вектора списком
#include <map> // для ассоциативного массива символов в toString()
using namespace std;

namespace dts {
	

	// Связанный список
	// Доступны два набора функций: итеративные и рекурсивные. По умолчанию используются итеративные. Чтобы включить второй набор, пропишите #define RECURSIVE_LL_FUNCTIONS
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
			LinkedElement(const T& _value) {
				value = _value;
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
				return;
			}
		}
		void iterativePrint() {
			if (_first == nullptr) return;
			LinkedElement* l = _first;
			for (int i = 0; i < _size; i++) {
				cout << l->value << " ";
				l = l->next;
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
				return;
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
				throw out_of_range("Неверный индекс связанного списка");
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
			if (index < 0 || index >= _size) throw out_of_range("Неверный индекс связанного списка");

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

		
		T popI(int index) {
			LinkedElement* linkedElem = _first;
			for (int curr = 0; curr + 1 != index; curr++) {
				linkedElem = linkedElem->next;
			}
			T value = linkedElem->next->value;
			delete linkedElem->next;
			linkedElem->next = nullptr;
			return value;
		}

		int findLeftR(LinkedElement* linkedElem, const T& elem, int currIndex = 0) {
			if (linkedElem->value == elem) {
				return currIndex;
			} else {
				return findLeftR(linkedElem->next, elem, currIndex + 1);
			}
		}
		int findRightR(LinkedElement* linkedElem, const T& elem, int currIndex = 0, int lastFoundIndex = 0) {
			if (linkedElem == nullptr || linkedElem->next == nullptr) {
				if (lastFoundIndex == 0) return -1;
				return lastFoundIndex;
			}
			if (linkedElem->value == elem) {
				lastFoundIndex = currIndex;
			}
			lastFoundIndex = findRightR(linkedElem->next, elem, currIndex + 1, lastFoundIndex);
			
			return lastFoundIndex;
			
		}
	public:
		int find(const T& elem, bool right = false) {
			if (!right)return findLeftR(_first, elem);
			else return findRightR(_first, elem);
		}
		linked_list() {
			_first = nullptr;
			_size = 0;
		}
		linked_list(const std::initializer_list<T> il) : linked_list() {
			for (int i = 0; i < il.size(); i++) {
				push_back(*(il.begin() + i));
			}
			_size = il.size();
		}
		linked_list(const linked_list& orig) {
			if (_size != 0) clear();

			if (orig._first == nullptr) {
				_first = nullptr;
				_size = 0;
			}
			else {

				_first = new LinkedElement(orig._first->value);
				LinkedElement* linkedElem = _first;
				LinkedElement* origLinkedElem = orig._first;
				while (origLinkedElem->next != nullptr) {
					linkedElem->next = new LinkedElement(origLinkedElem->next->value);
					linkedElem = linkedElem->next;
					origLinkedElem = origLinkedElem->next;
				}
				_size = orig._size;
			}
		}
		

		linked_list<T>& operator=(const linked_list& orig) {
			if (_size != 0) clear();
			
			if (orig._first == nullptr) {
				_first = nullptr;
				_size = 0;
			}
			else {
			
				_first = new LinkedElement(orig._first->value);

				LinkedElement* linkedElem = _first;
				LinkedElement* origLinkedElem = orig._first;
				while (origLinkedElem->next != nullptr) {
					linkedElem->next = new LinkedElement(origLinkedElem->next->value);
					linkedElem = linkedElem->next;
					origLinkedElem = origLinkedElem->next;
				}
				_size = orig._size;
			}
			return *this;
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
#ifdef RECURSIVE_LL_FUNCTIONS
			addElemR(elem);
#else
			addElemI(elem);
#endif
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
#ifdef RECURSIVE_LL_FUNCTIONS
			return pop_backR();
#else 
			return pop_backI();
#endif
		}

		T pop(int index) {
#ifdef RECURSIVE_LL_FUNCTIONS
			return popR(index);
#else
			return popI(index);
#endif
		}

		void print() {
#ifdef RECURSIVE_LL_FUNCTIONS
			recursivePrint();
#else
			iterativePrint();
#endif
			cout << endl;
		}

		T& first() {
			return _first->value;
		}
		T& last() {
			return (*this)[_size - 1];
		}

		T& at(int index) {
			try {
#ifdef RECURSIVE_LL_FUNCTIONS
				return getElemR(index);
#else
				return getElemI(index);
#endif
			}
			catch (out_of_range err) {
				cerr << err.what() << endl;
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
		a.recursivePrint();
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
		String(const string& s) {
			if (!s.empty()){
				cstr = new char[s.size() + 1];
				strcpy(cstr, s.c_str());
			}
			else cstr = nullptr;

			_size = s.size();
		}
		explicit String(int size) {
			cstr = new char[size];
			cstr[0] = '\0'; // для strcat-совместимости
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
			if (cstr != nullptr) {
				delete[]cstr;
				cstr = nullptr;
				_size = 0;
			}
		}
		String& operator=(const String& s) {
			if (s.cstr != nullptr) {
				cstr = new char[strLen(s.cstr) + 1];
				strcpy(cstr, s.cstr);
			}
			else cstr = nullptr;
			_size = s._size;
			return *this;
		}
		String& operator=(const char* cs) {
			if (cs != nullptr) {
				cstr = new char[strLen(cs) + 1];
				strcpy(cstr, cs);
			}
			else cstr = nullptr;
			_size = strLen(cs);
			return *this;
		}

		int size() const {
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

		friend String& operator+=(const String& s1, const String& s2);
		friend String& operator+=(const String& s, const char* cs);
		friend String& operator+=(const String& s, int n);
		
		friend bool operator==(const String& s, const char* cs);
		friend bool operator!=(const String& s, const char* cs);

		friend class StringBuilder;
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
	String operator+(const String& s, char cs)
	{
		String result = s;
		result.append(cs);
		return result;
	}

	String& operator+=(String& s1, const String& s2)
	{
		String result = s1;
		result.append(s2);
		return s1 = result;
	}

	String& operator+=(String& s, const char* cs)
	{
		String result = s;
		result.append(cs);
		return s = result;
	}
	String& operator+=(String& s, const char cs)
	{
		String result = s;
		result.append(cs);
		return s = result;
	}
	String& operator+=(String& s, int n)
	{
		String result = s;
		result.append(toString(n));
		return s = result;
	}

	bool operator==(const String& s, const char* cs) {
		return _stricmp(s.cstr, cs) == 0;
	}
	bool operator!=(const String& s, const char* cs) {
		return _stricmp(s.cstr, cs) != 0;
	}

	class StringBuilder {
	private:
		char** s;
		int _size;
		int _capacity;

		void nullArr() {
			for (int i = 0; i < _capacity; i++) {
				s[i] = nullptr;
			}
		}
		void checkCapacity(int c) {
			if (c > _capacity) {
				_capacity *= 2;
				char** newS = new char*[_capacity];
				for (int i = 0; i < _size; i++) {
					newS[i] = s[i];
				}
				delete s;
				s = newS;
			}
		}
	public:
		
		StringBuilder(int capacity = 8) {
			if (capacity == 0) capacity = 8;
			
			_capacity = capacity;
			s = new char*[_capacity];
			nullArr();
			_size = 0;
		}
		

		StringBuilder(const char* cstr, int capacity = 8) {
			if (capacity == 0) capacity = 8;

			_capacity = capacity;
			s = new char* [capacity];
			nullArr();

			s[0] = new char[strlen(cstr) + 1];
			strcpy(s[0], cstr);
			_size = 1;
		}
		StringBuilder(char* cstr, int capacity = 8) {
			if (capacity == 0) capacity = 8;

			_capacity = capacity;
			s = new char* [capacity];
			nullArr();

			s[0] = new char[strlen(cstr) + 1];
			strcpy(s[0], cstr);
			_size = 1;
		}

		StringBuilder(String str, int capacity = 8) {
			if (capacity == 0) capacity = 8;
			_capacity = capacity;
			s = new char* [capacity];
			nullArr();
			s[0] = new char[str.size() + 1];
			strcpy(s[0], str.cstr);
			_size = 1;
		}
		~StringBuilder() {
			clear();
		}
		StringBuilder(const StringBuilder& orig) {
			_capacity = orig._capacity;
			s = new char* [orig._capacity];
			_size = orig._size;
			for (int i = 0; i < orig._size; i++) {
				s[i] = new char[strlen(orig.s[i]) + 1];
				strcpy(s[i], orig.s[i]);
			}
		}

		String toString() const {
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
		

		void setCapacity(unsigned int capacity) {
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
		
		int getCapacity() {
			return _capacity;
		}

		void append(const String& str, bool endline = false) {
			checkCapacity(_size+1);
			s[_size] = new char[str.size() + 1 + endline];
			strcpy(s[_size], str.cstr);
			//cout << s[_size];
			if (endline) {
				s[_size][str.size()] = '\n';
				s[_size][str.size() + 1] = '\0';
			};
			_size++;
		}
		void appendLine(const String& str) {
			append(str, true);
		}

		void clear() {
			for (int i = 0; i < _size; i++) {
				delete s[i];
			}
			delete s;
			s = nullptr;
			_size = 0;
			_capacity = 0;
		}
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

	ostream& operator<<(ostream& os, const StringBuilder& str) {
		os << str.toString();
		return os;
	}

	template <typename T>
	class BinaryTree {
	private:
		struct Node {
			T value;

			Node* left;
			Node* right;

			Node() {
				left = nullptr;
				right = nullptr;
			}
			Node(const T& elem, Node* _left = nullptr, Node* _right = nullptr) {
				left = _left;
				right = _right;
				value = elem;
			}
		};

		void addElemR(const T& elem, Node* node = nullptr) {
			if (_root == nullptr) {
				_root = new Node(elem);
				return;
			}

			if (node == nullptr) node = _root;

			if (elem >= node->value) {
				if (node->right != nullptr) {
					addElemR(elem, node->right);
					Balance(node, elem);
				}
				else {
					node->right = new Node(elem);
					return;
				}
			}
			else {
				if (node->left != nullptr) {
					addElemR(elem, node->left);
					Balance(node, elem);
				}
				else {
					node->left = new Node(elem);
					return;
				}
			}
		}

		int getHeightR(Node* node = nullptr) {
			if (node == nullptr)
				return 0;
			else
			{
				int lDepth = getHeightR(node->left);
				int rDepth = getHeightR(node->right);

				if (lDepth > rDepth)
					return(lDepth + 1);
				else return(rDepth + 1);
			}
		}

		void Balance(Node*& node, const T& elem) {
			int LHeight = getHeightR(node->left);
			int RHeight = getHeightR(node->right);
			if (LHeight - RHeight > 1) {
				if (elem >= node->left->value) {
					rightRotate(node);
				}
				else {
					bigRightRotate(node);
				}
			}
			else if (LHeight - RHeight < -1) {
				if (elem >= node->right->value) {
					leftRotate(node);
				}
				else {
					bigRightRotate(node);
				}
			}
		}
		void BalanceR(Node*& node, const T& elem) {
			if (node == nullptr) return;

			BalanceR(node->left);
			BalanceR(node->right);

			int LHeight = getHeightR(node->left);
			int RHeight = getHeightR(node->right);
			if (LHeight - RHeight > 1) {
				if (elem >= node->left->value) {
					rightRotate(node);
				}
				else {
					bigRightRotate(node);
				}
			}
			else if (LHeight - RHeight < -1) {
				if (elem >= node->right->value) {
					leftRotate(node);
				}
				else {
					bigRightRotate(node);
				}
			}

		}

		bool findR(const T& elem, Node* node = nullptr) {
			if (node->value == elem) return true;

			if (elem >= node->value) {
				if (node->right != nullptr) {
					return findR(elem, node->right);
				}
				else return false;
			}
			else {
				if (node->left != nullptr) {
					return findR(elem, node->left);
				}
				else return false;
			}
		}
		void inOrderPrint(Node* node) {
			if (node == nullptr) return;

			inOrderPrint(node->left);
			cout << node->value << " ";
			inOrderPrint(node->right);
		}

		void rightRotate(Node*& node) {
			if (node == nullptr) return;
			Node* nodeCopy = new Node(node->value, node->left, node->right);
			Node* tmp = nodeCopy->left;
			nodeCopy->left = tmp->right;
			tmp->right = nodeCopy;

			*node = *tmp;
			delete tmp;
		}

		void leftRotate(Node*& node) {
			if (node == nullptr) return;

			// x - node
			//  \
			//   y
			//    \
			//     z

			Node* nodeCopy = new Node(node->value, node->left, node->right);

			Node* tmp = nodeCopy->right;
			nodeCopy->right = tmp->left;
			tmp->left = nodeCopy;
			*node = *tmp;
			delete tmp;
		}
		void bigRightRotate(Node*& node) {
			rightRotate(node->right);

			leftRotate(node);
		}

		void bigLeftRotate(Node*& node) {
			leftRotate(node->left);
			rightRotate(node);
		}

		void printR(const std::string& prefix, const Node* node, bool isLeft)
		{
			if (node != nullptr)
			{
				std::cout << prefix;

				std::cout << (isLeft ? (char)195 : (char)192) << (char)196 << (char)196;

				// print the value of the node
				std::cout << node->value << std::endl;

				// enter the next tree level - left and right branch
				printR(prefix + (isLeft ? (char)179 : ' ') + "   ", node->left, true);
				printR(prefix + (isLeft ? (char)179 : ' ') + "   ", node->right, false);
			}
		}

		Node* _root;

	public:






		BinaryTree() {
			_root = nullptr;
		}
		~BinaryTree() {
			clear();
		}

		void clearR(Node*& node) {
			if (node == nullptr) return;

			if (node->left != nullptr) {
				clearR(node->left);
			}
			if (node->right != nullptr) {
				clearR(node->right);
			}
			delete node;
			node = nullptr;
		}
		void clear() {
			clearR(_root);


		}

		void addElem(const T& elem) {
			addElemR(elem);
		}
		int getHeight() {
			return getHeightR(_root) - 1;
		}
		bool removeR(Node*& node, const T& elem) {
			if (node == nullptr) return false;

			if (elem > node->value) {
				return removeR(node->right, elem);
			}
			else if (elem < node->value) {
				return removeR(node->left, elem);
			}
			else {
				if (node->left == nullptr && node->right == nullptr) {

					delete node;
					node = nullptr;
				}
				else if (node->left != nullptr) {

					Node*& largestLeftChild = node->left;
					while (largestLeftChild->right != nullptr) {
						largestLeftChild = largestLeftChild->right;
					}
					node->value = largestLeftChild->value;
					delete largestLeftChild;
					largestLeftChild = nullptr;
				}
				else if (node->right != nullptr) {
					Node* right = node->right;
					delete node;
					node = right;
				}

				return true;
			}

		}
		bool find(const T& elem) {
			return findR(elem, _root);
		};


		bool remove(const T& elem) {
			bool result = removeR(_root, elem);
			BalanceR(_root, elem);
			return result;
		}

		// In Order
		void printIO() {
			inOrderPrint(_root);
		}



		void print()
		{
			system("cls");
			printR("", _root, false);
			system("pause");
		}
	};

	template <typename T>
	int partition(T arr[], int low, int high)
	{
		int pivot = arr[high];    // pivot 
		int i = (low - 1);

		for (int j = low; j <= high - 1; j++)
		{
			//if current element is smaller than pivot, increment the low element
			//swap elements at i and j
			if (arr[j] <= pivot)
			{
				i++;    // increment index of smaller element 
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[high]);
		return (i + 1);
	}


	template <typename T>
	void quickSort(T*& arr, int low, int high)
	{
		if (low < high)
		{
			//partition the array 
			T pivot = partition(arr, low, high);

			//sort the sub arrays independently 
			quickSort(arr, low, pivot - 1);
			quickSort(arr, pivot + 1, high);
		}
	}
}






