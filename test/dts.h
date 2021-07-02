#pragma once
#ifndef DTS_INCLUDED
#define DTS_INCLUDED
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <mutex> // для инициализации вектора списком
#include <map> // для ассоциативного массива символов в toString()
using namespace std;

namespace dts {
	template<typename T>
	class double_linked_list;
	template<typename T>
	class linked_list;
	template<typename T>
	class Stack;
	template<typename T>
	class Queue;
	template<typename Type>
	class Vector;

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

		void recursivePrint(LinkedElement* l = nullptr);
		void iterativePrint();

		void addElemR(const T elem, LinkedElement* linkedElem = nullptr);
		void addElemI(const T elem);
		T& getElemR(int index, int current = 0, LinkedElement* linkedElem = nullptr);
		T& getElemI(int index);
		T& pop_backR(LinkedElement* linkedElem = nullptr);
		T& pop_backI();
		void bubbleSortCycleR(LinkedElement* linkedElem = nullptr);
		void bubbleSortI();
		T popR(int index, LinkedElement* linkedElem = nullptr, int current = 0);

		
		T popI(int index);

		int findLeftR(LinkedElement* linkedElem, const T& elem, int currIndex = 0);
		int findRightR(LinkedElement* linkedElem, const T& elem, int currIndex = 0, int lastFoundIndex = 0);
	public:
		int find(const T& elem, bool right = false);
		linked_list();
		linked_list(const std::initializer_list<T> il);
		linked_list(const linked_list& orig);
		

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

		~linked_list();
		
		linked_list* clear();

		// Процедурные оболочки рекурсивных функций
		linked_list* push_back(const T elem);

		linked_list* push_front(const T elem);
		T pop_front();
		T pop_back();

		T pop(int index);

		void print();

		T& first();
		T& last();

		T& at(int index);

		T& operator[](int index) {
			return at(index);
		}

		int size();
		template<typename T>
		friend void bubbleSort(linked_list<T>& a);

		template<typename type>
		friend ostream& operator<<(ostream& os, linked_list<type>& a);
	
		double_linked_list<T> toDoubleList();
		Vector<T> toArray();
	};
	template<typename T>
	inline void bubbleSort(linked_list<T>& a) { // Работает только с численными списками
		string tID = typeid(T).name();
		if (tID == "int" || tID == "float" || tID == "double") {
			for (int i = 0; i < a._size; i++) {
				a.bubbleSortCycleR();
			}
		}
	}
	template<typename type>
	ostream& operator<<(ostream& os, linked_list<type>& a) {
		a.recursivePrint();
		return os;
	}

	template <typename T>
	class double_linked_list {
	private:

		class LinkedElement {
		public:

			T value;
			LinkedElement* next;
			LinkedElement* prev;
			LinkedElement() {
				next = nullptr;
				prev = nullptr;
			}
			LinkedElement(const T& _value, LinkedElement* _next = nullptr, LinkedElement* _prev = nullptr) {
				value = _value;
				next = _next;
				prev = _prev;
			}
		};



		LinkedElement* _first;
		LinkedElement* _last;
		int _size;

		void recursivePrint(LinkedElement* l = nullptr);
		void iterativePrint();

		void pushFront(const T& elem);

		

		

		T& getElemFirst(int index);
		T& getElemLast(int index);
		

		void bubbleSortCycleR(LinkedElement* linkedElem = nullptr);
		void bubbleSortI();


		T popFirst(int index);
		T popLast(int index);

		int findLeftR(LinkedElement* linkedElem, const T& elem, int currIndex = 0);
		int findRightR(LinkedElement* linkedElem, const T& elem, int currIndex = 0, int lastFoundIndex = 0);
	public:
		int find(const T& elem, bool right = false);
		double_linked_list();
		double_linked_list(const std::initializer_list<T> il);
		double_linked_list(const double_linked_list& orig);


		double_linked_list<T>& operator=(const double_linked_list& orig) {
			if (_size != 0) clear();

			
			if (orig._first == nullptr) {
				_first = nullptr;
				_last = _first;
				_size = 0;
			}
			else {

				_first = new LinkedElement(orig._first->value);
				LinkedElement* linkedElem = _first;
				LinkedElement* origLinkedElem = orig._first;
				while (origLinkedElem->next != nullptr) {
					linkedElem->next = new LinkedElement(origLinkedElem->next->value, nullptr, linkedElem);
					linkedElem = linkedElem->next;
					origLinkedElem = origLinkedElem->next;
				}
				_last = linkedElem;
				_size = orig._size;
			}
			return *this;
		}

		~double_linked_list();

		double_linked_list* clear();

		// Процедурные оболочки рекурсивных функций
		double_linked_list* push_back(const T& elem);

		double_linked_list* push_front(const T& elem);
		T pop_back();
		T pop_front();

		T pop(int index);

		void print();

		T& first();
		T& last();

		T& at(int index);

		T& operator[](int index) {
			return at(index);
		}

		int size() const;
		template<typename T>
		friend void bubbleSort(double_linked_list<T>& a);

		template<typename type>
		friend ostream& operator<<(ostream& os, double_linked_list<type>& a);

		linked_list<T> toList();
		Vector<T> toArray();
	};

	template<typename type>
	inline ostream& operator<<(ostream& os, double_linked_list<type>& a) {
		a.recursivePrint();
		return os;
	}

	template <typename T>
	class Deque {
	private:
		double_linked_list<T> deque;
	public:
		Deque() {};

		Deque* enqueueFirst(const T& elem);
		Deque* enqueueLast(const T& elem);

		T dequeueFirst();
		T dequeueLast();
		T& first();
		T& last();
		int count() const;
		T& operator[](unsigned int index) const {
			return deque.at(index);
		}

		
		friend class Queue<T>;
		friend class Stack<T>;
	};

	template <typename T>
	class Stack {
	private:
		Deque<T> stack;
		
	public:
		Stack() {};
		Stack(initializer_list<T> il) {
			while (count() != 0) pop();

			for (int i = 0; i < il.size(); i++) {
				stack.enqueueLast(*(il.begin() + i));
			}
		}

		Stack* push(const T& elem);
		T pop();
		T peek() const;
		int count() const;

	};

	template <typename T>
	class Queue {
	private:
		Deque<T> queue;
	public:

		Queue* enqueue(const T& elem);
		T dequeue();
		T& first();
		T& last();
		int count();
	};

	

	// Вектор(динамический массив)
	template <typename Type>
	class Vector
	{
	private:
		Type* arr;
		int _size;
	public:
		Vector();
		Vector(const Vector& orig);
		Vector(std::initializer_list<Type> _arr);
		void operator=(std::initializer_list<Type> _arr) {

			if (arr != nullptr) {
				delete[]arr;
				arr = nullptr;
			}
			_size = _arr._size;

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
		~Vector();

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

		void push_back(const Type& elem);

		int size() const;

		bool empty() const;

		int find(const Type& elem, bool right = false);

		Type& at(int index);

		Type& operator[](int index) {
			if (index >= 0 && index < _size) return arr[index];
		}

		bool remove(int index = -1);

		void print() const;

		linked_list<Type> toList();
		double_linked_list<Type> toDoubleList();
		
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
		const char* c_str();

		operator string() const {
			string result;
			for (int i = 0; cstr[i] != '\0'; i++) {
				result.push_back(cstr[i]);
			}
			return result;
		}

		String();
		String(const string& s);
		explicit String(int size);
		String(const String& s);
		String(const char* cs);
		~String();
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

		int size() const;
		int length();
		String& append(const String& s);
		String& append(char s);

		String& reverse();

		char& at(int index);
		char& operator[](int index) {
			return at(index);
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

	inline String operator+(const String& s, const char* cs)
	{
		String result = s;
		result.append(cs);
		return result;
	}

	inline String operator+(const String& s, int n)
	{
		String result = s;
		result.append(toString(n));
		return result;
	}
	inline String operator+(const String& s, char cs)
	{
		String result = s;
		result.append(cs);
		return result;
	}

	inline String& operator+=(String& s1, const String& s2)
	{
		String result = s1;
		result.append(s2);
		return s1 = result;
	}

	inline String& operator+=(String& s, const char* cs)
	{
		String result = s;
		result.append(cs);
		return s = result;
	}
	inline String& operator+=(String& s, const char cs)
	{
		String result = s;
		result.append(cs);
		return s = result;
	}
	inline String& operator+=(String& s, int n)
	{
		String result = s;
		result.append(toString(n));
		return s = result;
	}

	inline bool operator==(const String& s, const char* cs) {
		return _stricmp(s.cstr, cs) == 0;
	}
	inline bool operator!=(const String& s, const char* cs) {
		return _stricmp(s.cstr, cs) != 0;
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

	template <typename T, typename V>
	class BinaryTree {
	private:
		struct Node {
			
			T key;
			V value;

			Node* left;
			Node* right;

			Node();
			Node(const T& _key, const V& _value, Node* _left = nullptr, Node* _right = nullptr);
			Node(const T& _key, Node* _left = nullptr, Node* _right = nullptr) {
				value = key;
			};
		};

		void addElemR(const T& key, const V& value, Node* node = nullptr);

		int getHeightR(Node* node = nullptr);

		void Balance(Node*& node, const T& elem);
		void BalanceR(Node*& node, const T& elem);

		bool countR(const T& elem, Node* node = nullptr);
		void inOrderPrint(Node* node);

		void rightRotate(Node*& node);

		void leftRotate(Node*& node);
		void bigRightRotate(Node*& node);

		void bigLeftRotate(Node*& node);

		void printR(const std::string& prefix, const Node* node, bool isLeft, bool rightExists = false);
		V& findR(const T& key, Node* node);
		Node* _root;
		bool removeR(Node*& node, const T& key);
		Node* lastFound;

	public:
		BinaryTree();
		~BinaryTree();

		void clearR(Node*& node);
		void clear();

		void push(const T& key, const V& value);
		int getHeight();
		
		bool count(const T& key);;


		bool remove(const T& key);

		// In Order
		void printIO();

		void print();

		
		V& find(const T& key);

		V& operator[](const T& key){
			return find(key);
		}
	};

	template <typename T>
	inline int partition(T arr[], int low, int high)
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
	inline void quickSort(T*& arr, int low, int high)
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
	template<typename T>
	inline void linked_list<T>::recursivePrint(LinkedElement* l) { // Рекурсивная начинка вывода списка
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
	template<typename T>
	inline void linked_list<T>::iterativePrint() {
		if (_first == nullptr) return;
		LinkedElement* l = _first;
		for (int i = 0; i < _size; i++) {
			cout << l->value << " ";
			l = l->next;
		}
	}
	template<typename T>
	inline void linked_list<T>::addElemR(const T elem, LinkedElement* linkedElem) { // Рекурсивная начинка добавления объекта в список
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
	template<typename T>
	inline void linked_list<T>::addElemI(const T elem) { // Итеративная начинка добавления объекта в список
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
		_size++;
	}
	template<typename T>
	inline T& linked_list<T>::getElemR(int index, int current, LinkedElement* linkedElem) { // Рекурсивная начинка нахождения n-ного объекта списка
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
	template<typename T>
	inline T& linked_list<T>::getElemI(int index) { // Итеративная начинка нахождения n-ного объекта списка
		if (index < 0 || index >= _size) throw out_of_range("Неверный индекс связанного списка");

		LinkedElement* linkedElem = _first;
		for (int current = 0; current != index; current++) {
			linkedElem = linkedElem->next;
		}
		return linkedElem->value;
	}
	template<typename T>
	inline T& linked_list<T>::pop_backR(LinkedElement* linkedElem) { // Рекурсивная начинка удаления последнего объекта списка
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
	template<typename T>
	inline T& linked_list<T>::pop_backI() { // Итеративная начинка удаления последнего объекта списка
		LinkedElement* linkedElem = _first;
		while (linkedElem->next->next != nullptr) {
			linkedElem = linkedElem->next;
		}
		T value = linkedElem->next->value;
		delete linkedElem->next;
		linkedElem->next = nullptr;
		_size--;
		return value;
	}
	template<typename T>
	inline void linked_list<T>::bubbleSortCycleR(LinkedElement* linkedElem) { // Метод, проводящий один цикл пузырьковой сортировки(повторяется нужное количество раз уже в bubbleSort()
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
	template<typename T>
	inline void linked_list<T>::bubbleSortI() {
		LinkedElement linkedElem = _first;
		for (int i = 0; i < _size; i++) {
			if (linkedElem->value > linkedElem->next->value) {
				swap(linkedElem->value, linkedElem->next->value);

			}
			linkedElem = linkedElem->next;
		}
	}
	template<typename T>
	inline T linked_list<T>::popR(int index, LinkedElement* linkedElem, int current) {
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
		if (index != current + 1) {
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
	template<typename T>
	inline T linked_list<T>::popI(int index) {
		LinkedElement* linkedElem = _first;
		for (int curr = 0; curr + 1 != index; curr++) {
			linkedElem = linkedElem->next;
		}
		T value = linkedElem->next->value;
		delete linkedElem->next;
		linkedElem->next = nullptr;
		return value;
	}
	template<typename T>
	inline int linked_list<T>::findLeftR(LinkedElement* linkedElem, const T& elem, int currIndex) {
		if (linkedElem == nullptr) return -1;

		if (linkedElem->value == elem) {
			return currIndex;
		}
		else {
			return findLeftR(linkedElem->next, elem, currIndex + 1);
		}
	}
	template<typename T>
	inline int linked_list<T>::findRightR(LinkedElement* linkedElem, const T& elem, int currIndex, int lastFoundIndex) {
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
	template<typename T>
	inline int linked_list<T>::find(const T& elem, bool right) {
		if (!right)return findLeftR(_first, elem);
		else return findRightR(_first, elem);
	}
	template<typename T>
	inline linked_list<T>::linked_list() {
		_first = nullptr;
		_size = 0;
	}
	template<typename T>
	inline linked_list<T>::linked_list(const std::initializer_list<T> il) : linked_list() {
		for (int i = 0; i < il.size(); i++) {
			push_back(*(il.begin() + i));
		}
		_size = il.size();
	}
	template<typename T>
	inline linked_list<T>::linked_list(const linked_list& orig) {
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
	template<typename T>
	inline linked_list<T>::~linked_list() {
		clear();
	}
	template<typename T>
	inline linked_list<T>* linked_list<T>::clear() {
		while (_size != 0) pop_front();
		return this;
	}

	// Процедурные оболочки рекурсивных функций
	template<typename T>
	inline linked_list<T>* linked_list<T>::push_back(const T elem) {
#ifdef RECURSIVE_LL_FUNCTIONS
		addElemR(elem);
#else
		addElemI(elem);
#endif
		return this;
	}
	template<typename T>
	inline linked_list<T>* linked_list<T>::push_front(const T elem) {
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
	template<typename T>
	inline T linked_list<T>::pop_front() {
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
	template<typename T>
	inline T linked_list<T>::pop_back() {
#ifdef RECURSIVE_LL_FUNCTIONS
		return pop_backR();
#else 
		return pop_backI();
#endif
	}
	template<typename T>
	inline T linked_list<T>::pop(int index) {
#ifdef RECURSIVE_LL_FUNCTIONS
		return popR(index);
#else
		return popI(index);
#endif
	}
	template<typename T>
	inline void linked_list<T>::print() {
#ifdef RECURSIVE_LL_FUNCTIONS
		recursivePrint();
#else
		iterativePrint();
#endif
		cout << endl;
	}
	template<typename T>
	inline T& linked_list<T>::first() {
		return _first->value;
	}
	template<typename T>
	inline T& linked_list<T>::last() {
		return (*this)[_size - 1];
	}
	template<typename T>
	inline T& linked_list<T>::at(int index) {
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
	template<typename T>
	inline int linked_list<T>::size() {
		return _size;
	}
	template<typename T>
	inline double_linked_list<T> linked_list<T>::toDoubleList() {
		double_linked_list<T> result;
		LinkedElement node;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline Vector<T> linked_list<T>::toArray() {
		Vector<T> result;
		LinkedElement node;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline void double_linked_list<T>::recursivePrint(LinkedElement* l) { // Рекурсивная начинка вывода списка
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
	template<typename T>
	inline void double_linked_list<T>::iterativePrint() {
		if (_first == nullptr) return;
		LinkedElement* l = _first;
		for (int i = 0; i < _size; i++) {
			cout << l->value << " ";
			l = l->next;
		}
	}
	template<typename T>
	inline void double_linked_list<T>::pushFront(const T& elem) {
		if (_first == nullptr) {
			_first = new LinkedElement(elem);
			_last = _first;
		}
		_first->prev = new LinkedElement(elem);
		_first = _first->prev;
	}
	template<typename T>
	inline T& double_linked_list<T>::getElemLast(int index) { // нахождение с конца
		if (index < 0 || index >= _size) throw out_of_range("Неверный индекс связанного списка");

		LinkedElement* linkedElem = _last;
		for (int current = _size-1; current != index; current--) {
			linkedElem = linkedElem->prev;
		}
		return linkedElem->value;
	}
	template<typename T>
	inline T& double_linked_list<T>::getElemFirst(int index) { // нахождение с начала
		if (index < 0 || index >= _size) throw out_of_range("Неверный индекс связанного списка");

		LinkedElement* linkedElem = _first;
		for (int current = 0; current != index; current++) {
			linkedElem = linkedElem->next;
		}
		return linkedElem->value;
	}
	template<typename T>
	inline void double_linked_list<T>::bubbleSortCycleR(LinkedElement* linkedElem) { // Метод, проводящий один цикл пузырьковой сортировки(повторяется нужное количество раз уже в bubbleSort()
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
	template<typename T>
	inline void double_linked_list<T>::bubbleSortI() {
		LinkedElement linkedElem = _first;
		for (int i = 0; i < _size; i++) {
			if (linkedElem->value > linkedElem->next->value) {
				swap(linkedElem->value, linkedElem->next->value);

			}
			linkedElem = linkedElem->next;
		}
	}
	template<typename T>
	inline T double_linked_list<T>::popLast(int index) {
		LinkedElement* linkedElem = _first;
		for (int curr = _size-1; curr != index; curr--) {
			linkedElem = linkedElem->prev;
		}
		T value = linkedElem->value;
		linkedElem->prev->next = linkedElem->next;
		linkedElem->next->prev = linkedElem->prev;
		delete linkedElem;
		linkedElem = nullptr;
		_size--;
		return value;
	}
	template<typename T>
	inline T double_linked_list<T>::popFirst(int index) {
		LinkedElement* linkedElem = _first;
		for (int curr = 0; curr != index; curr++) {
			linkedElem = linkedElem->next;
		}
		T value = linkedElem->value;
		linkedElem->prev->next = linkedElem->next;
		linkedElem->next->prev = linkedElem->prev;
		delete linkedElem;
		linkedElem = nullptr;
		_size--;
		return value;
	}
	template<typename T>
	inline int double_linked_list<T>::findLeftR(LinkedElement* linkedElem, const T& elem, int currIndex) {
		if (linkedElem->value == elem) {
			return currIndex;
		}
		else {
			return findLeftR(linkedElem->next, elem, currIndex + 1);
		}
	}
	template<typename T>
	inline int double_linked_list<T>::findRightR(LinkedElement* linkedElem, const T& elem, int currIndex, int lastFoundIndex) {
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
	template<typename T>
	inline int double_linked_list<T>::find(const T& elem, bool right) {
		if (!right)return findLeftR(_first, elem);
		else return findRightR(_first, elem);
	}
	template<typename T>
	inline double_linked_list<T>::double_linked_list() {
		_first = nullptr;
		_last = nullptr;
		_size = 0;
	}
	template<typename T>
	inline double_linked_list<T>::double_linked_list(const std::initializer_list<T> il) : double_linked_list() {
		for (int i = 0; i < il.size(); i++) {
			push_back(*(il.begin() + i));
		}
		_size = il.size();
	}
	template<typename T>
	inline double_linked_list<T>::double_linked_list(const double_linked_list& orig) {
		//if (_size != 0) clear();

		if (orig._first == nullptr) {
			_first = nullptr;
			_last = _first;
			_size = 0;
		}
		else {

			_first = new LinkedElement(orig._first->value);
			LinkedElement* linkedElem = _first;
			LinkedElement* origLinkedElem = orig._first;
			while (origLinkedElem->next != nullptr) {
				linkedElem->next = new LinkedElement(origLinkedElem->next->value, nullptr, linkedElem);
				linkedElem = linkedElem->next;
				origLinkedElem = origLinkedElem->next;
			}
			_last = linkedElem;
			_size = orig._size;
		}
	}
	template<typename T>
	inline double_linked_list<T>::~double_linked_list() {
		clear();
	}
	template<typename T>
	inline double_linked_list<T>* double_linked_list<T>::clear() {
		while (_size != 0) pop_front();
		return this;
	}

	// Процедурные оболочки рекурсивных функций
	template<typename T>
	inline double_linked_list<T>* double_linked_list<T>::push_back(const T& elem) {

		if (_last == nullptr) {
			_last = new LinkedElement(elem);
			_first = _last;
		}
		else {
			LinkedElement* oldLast = _last;

			oldLast->next = new LinkedElement(elem, nullptr, oldLast);
			_last = oldLast->next;
		}
		_size++;

		return this;
	}
	template<typename T>
	inline double_linked_list<T>* double_linked_list<T>::push_front(const T& elem) {
		if (_first == nullptr) {
			_first = new LinkedElement(elem);
			_last = _first;
		}
		else {
			LinkedElement* oldFirst = _first;
			_first = new LinkedElement(elem, oldFirst);
			oldFirst->prev = _first;
		}
		_size++;
		return this;
	}
	template<typename T>
	inline T double_linked_list<T>::pop_back() {
		if (_last == nullptr) throw runtime_error("Список пуст");

		T value = _last->value;
		LinkedElement* prev = _last->prev;
		if (prev == nullptr) {
			delete _first;
			_first = nullptr;
			_last = _first;
			_size--;
			return value;
		}
		delete prev->next;
		prev->next = nullptr;
		_last = prev;
		_size--;
		return value;
	}
	template<typename T>
	inline T double_linked_list<T>::pop_front() {
		if (_first == nullptr) throw runtime_error("Список пуст");
		T value = _first->value;
		LinkedElement* next = _first->next;
		if (next == nullptr) {
			_size--;
			delete _first;
			_first = nullptr;
			_last = _first;
			return value;
		}
		delete next->prev;
		next->prev = nullptr;
		_first = next;
		_size--;
		if (_first == nullptr) _last = nullptr;
		return value;
	}
	template<typename T>
	inline T double_linked_list<T>::pop(int index) {
		if (index == 0) {
			return pop_front();
		}
		else if(index == _size - 1){
			return pop_back();
		}
		
		if (index <= _size / 2 - 1) {
			return popFirst(index);
		}
		else {
			return popLast(index);
		}
	}
	template<typename T>
	inline void double_linked_list<T>::print() {
#ifdef RECURSIVE_LL_FUNCTIONS
		recursivePrint();
#else
		iterativePrint();
#endif
		cout << endl;
	}
	template<typename T>
	inline T& double_linked_list<T>::first() {
		return _first->value;
	}
	template<typename T>
	inline T& double_linked_list<T>::last() {
		return _last->value;
	}
	template<typename T>
	inline T& double_linked_list<T>::at(int index) {
		try {
			if (index <= _size / 2 - 1) {
				return getElemFirst(index);
			}
			else {
				return getElemLast(index);
			}
		}
		catch (out_of_range err) {
			cerr << err.what() << endl;
		}
	}
	template<typename T>
	inline int double_linked_list<T>::size() const {
		return _size;
	}
	template<typename T>
	inline linked_list<T> double_linked_list<T>::toList() {
		linked_list<T> result;
		LinkedElement node;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline Vector<T> double_linked_list<T>::toArray() {
		Vector<T> result;
		LinkedElement node;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline Deque<T>* Deque<T>::enqueueFirst(const T& elem) {
		deque.push_front(elem);
		return this;
	}
	template<typename T>
	inline Deque<T>* Deque<T>::enqueueLast(const T& elem) {
		deque.push_back(elem);
		return this;
	}
	template<typename T>
	inline T Deque<T>::dequeueFirst() {
		return deque.pop_front();

	}
	template<typename T>
	inline T Deque<T>::dequeueLast() {
		return deque.pop_back();
	}
	template<typename T>
	inline T& Deque<T>::first() {
		return deque.first();
	}
	template<typename T>
	inline T& Deque<T>::last() {
		return deque.last();
	}
	template<typename T>
	inline int Deque<T>::count() const {
		return deque.size();
	}
	template<typename T>
	inline Stack<T>* Stack<T>::push(const T& elem) {
		stack.enqueueLast(elem);
		return this;
	}
	template<typename T>
	inline T Stack<T>::pop() {
		if (stack.count() == 0) {
			throw "Стек пуст!";
		}
		return stack.dequeueLast();
	}
	template<typename T>
	inline T Stack<T>::peek() const {
		if (stack.count() == 0) {
			throw "Стек пуст!";
		}
		return stack.last();
	}
	template<typename T>
	inline int Stack<T>::count() const {
		return stack.count();
	}
	template<typename T>
	inline Queue<T>* Queue<T>::enqueue(const T& elem) {
		queue.enqueueFirst(elem);
		return this;
	}
	template <typename T>
	inline T& Queue<T>::first() {
		return queue.first();
	}
	template <typename T>
	inline T& Queue<T>::last() {
		return queue.last();
	}
	

	template<typename T>
	inline T Queue<T>::dequeue() {
		if (queue.count() == 0) {
			throw "Стек пуст!";
		}
		return queue.dequeueLast();
	}
	
	template<typename T>
	inline int Queue<T>::count() {
		return queue.count();
	}
	template<typename Type>
	inline Vector<Type>::Vector() {
		arr = nullptr;
		_size = 0;
	}
	template<typename Type>
	inline Vector<Type>::Vector(const Vector& orig) {
		_size = orig._size;
		arr = new Type[orig._size];
		for (int i = 0; i < _size; i++) {
			arr[i] = orig.arr[i];
		}
	}
	template<typename Type>
	inline Vector<Type>::Vector(std::initializer_list<Type> _arr) {


		arr = new Type[_arr.size()];
		_size = _arr.size();
		for (int i = 0; i < _size; i++) {
			arr[i] = *(_arr.begin() + i);
		}
	}
	template<typename Type>
	inline Vector<Type>::~Vector() {
		if (arr != nullptr) {
			delete[]arr;
			arr = nullptr;
		}
		_size = 0;
	}
	template<typename Type>
	inline void Vector<Type>::push_back(const Type& elem) {

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
	template<typename Type>
	inline int Vector<Type>::size() const {
		return _size;
	}
	template<typename Type>
	inline bool Vector<Type>::empty() const {
		return _size == 0;
	}
	template<typename Type>
	inline int Vector<Type>::find(const Type& elem, bool right) {
		int index = -1;
		for (int i = 0; i < _size; i++) {
			if (arr[i] == elem) {
				index = i;
				if (!right) return index;
			}
		}
		return index;
	}
	template<typename Type>
	inline Type& Vector<Type>::at(int index) {
		if (index >= 0 && index < _size) return arr[index];
	}
	template<typename Type>
	inline bool Vector<Type>::remove(int index) {
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
	template<typename Type>
	inline void Vector<Type>::print() const {
		for (int i = 0; i < _size; i++) {
			std::cout << arr[i] << " ";
		}
	}
	template<typename Type>
	inline linked_list<Type> Vector<Type>::toList() {
		linked_list<Type> result;
		for (int i = 0; i < _size; i++) {
			result.push_back(arr[i]);
		}
		return result;
	}
	template<typename Type>
	inline double_linked_list<Type> Vector<Type>::toDoubleList() {
		double_linked_list<Type> result;
		for (int i = 0; i < _size; i++) {
			result.push_back(arr[i]);
		}
		return result;
	}
	template<typename T, typename V>
	inline BinaryTree<T, V>::Node::Node() {
		left = nullptr;
		right = nullptr;
	}
	template<typename T, typename V>
	inline BinaryTree<T,V>::Node::Node(const T& _key, const V& _value, Node* _left, Node* _right) {
		left = _left;
		right = _right;
		key = _key;
		value = _value;
	}
	template<typename T, typename V>
	inline void BinaryTree<T, V>::addElemR(const T& key, const V& value, Node* node) {
		try {
			if (_root == nullptr) {
				_root = new Node(key, value);
				return;
			}

			if (node == nullptr) node = _root;

			if (key > node->key) {
				if (node->right != nullptr) {
					addElemR(key, value, node->right);
					Balance(node, key);
				}
				else {
					node->right = new Node(key, value);
					return;
				}
			}
			else if (key < node->key) {
				if (node->left != nullptr) {
					addElemR(key, value, node->left);
					Balance(node, key);
				}
				else {
					node->left = new Node(key, value);
					return;
				}
			}
			else throw runtime_error("Бинарное дерево: совпадающий ключ");
		}
		catch (runtime_error re) {
			cerr << endl << re.what() << endl;
		}
	}
	template<typename T, typename V>
	inline int BinaryTree<T, V>::getHeightR(Node* node) {
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
	template<typename T, typename V>
	inline void BinaryTree<T, V>::Balance(Node*& node, const T& key) {
		int LHeight = getHeightR(node->left);
		int RHeight = getHeightR(node->right);
		if (LHeight - RHeight > 1) {
			if (key >= node->left->key) {
				rightRotate(node);
			}
			else {
				bigRightRotate(node);
			}
		}
		else if (LHeight - RHeight < -1) {
			if (key >= node->right->key) {
				leftRotate(node);
			}
			else {
				bigRightRotate(node);
			}
		}
	}
	template<typename T, typename V>
	inline void BinaryTree<T, V>::BalanceR(Node*& node, const T& elem) {
		if (node == nullptr) return;

		BalanceR(node->left, elem);
		BalanceR(node->right, elem);

		int LHeight = getHeightR(node->left);
		int RHeight = getHeightR(node->right);
		if (LHeight - RHeight > 1) {
			if (elem >= node->left->key) {
				rightRotate(node);
			}
			else {
				bigRightRotate(node);
			}
		}
		else if (LHeight - RHeight < -1) {
			if (elem >= node->right->key) {
				leftRotate(node);
			}
			else {
				bigRightRotate(node);
			}
		}

	}
	template<typename T, typename V>
	inline bool BinaryTree<T, V>::countR(const T& key, Node* node) {
		if (node->key == key) return true;

		if (key > node->key) {
			if (node->right != nullptr) {
				lastFound = node->right;
				return countR(key, node->right);
			}
			else return false;
		}
		else {
			if (node->left != nullptr) {
				lastFound = node->left;
				return countR(key, node->left);
			}
			else return false;
		}
	}
	template<typename T, typename V>
	inline void BinaryTree<T, V>::inOrderPrint(Node* node) {
		if (node == nullptr) return;

		inOrderPrint(node->left);
		cout << node->value << " ";
		inOrderPrint(node->right);
	}
	template<typename T, typename V>
	inline void BinaryTree<T, V>::rightRotate(Node*& node) {
		if (node == nullptr) return;
		Node* nodeCopy = new Node(node->value, node->key, node->left, node->right);
		Node* tmp = nodeCopy->left;
		nodeCopy->left = tmp->right;
		tmp->right = nodeCopy;

		*node = *tmp;
		delete tmp;
	}
	template<typename T, typename V>
	inline void BinaryTree<T,V >::leftRotate(Node*& node) {
		if (node == nullptr) return;

		Node* nodeCopy = new Node(node->value, node->key, node->left, node->right);

		Node* tmp = nodeCopy->right;
		nodeCopy->right = tmp->left;
		tmp->left = nodeCopy;
		*node = *tmp;
		delete tmp;
	}
	template<typename T, typename V>
	inline void BinaryTree<T, V>::bigRightRotate(Node*& node) {
		rightRotate(node->right);

		leftRotate(node);
	}
	template<typename T, typename V>
	inline void BinaryTree<T, V>::bigLeftRotate(Node*& node) {
		leftRotate(node->left);
		rightRotate(node);
	}
	template<typename T, typename V>
	inline void BinaryTree<T,V>::printR(const std::string& prefix, const Node* node, bool isLeft, bool rightExists)
	{
		if (node != nullptr)
		{
			std::cout << prefix;

			std::cout << (isLeft && rightExists ? (char)195 : (char)192) << (char)196 << (char)196;

			// print the value of the node
			std::cout << node->value << std::endl;

			// enter the next tree level - left and right branch
			printR(prefix + (isLeft ? (char)179 : ' ') + "   ", node->left, true, node->right != nullptr);
			printR(prefix + (isLeft ? (char)179 : ' ') + "   ", node->right, false);
		}
	}
	template<typename T, typename V>
	inline V& BinaryTree<T, V>::findR(const T& key, Node* node) {
		try {
			if (node == nullptr)throw runtime_error("Бинарное дерево: findR не нашёл значение(дерево пустое)");

			if (node->key == key) return node->value;

			if (key > node->key) {
				if (node->right != nullptr) {
					return findR(key, node->right);
				}
				else throw runtime_error("Бинарное дерево: findR не нашёл значение");
			}
			else {
				if (node->left != nullptr) {
					return findR(key, node->left);
				}
				else throw runtime_error("Бинарное дерево: findR не нашёл значение");;
			}
		}
		catch (runtime_error re) {
			cerr << endl << re.what() << endl;
		}

	}
	template<typename T, typename V>
	inline BinaryTree<T, V>::BinaryTree() {
		_root = nullptr;
		lastFound = nullptr;
	}
	template<typename T, typename V>
	inline BinaryTree<T,V>::~BinaryTree() {
		clear();
	}
	template<typename T, typename V>
	inline void BinaryTree<T,V>::clearR(Node*& node) {
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
	template<typename T, typename V>
	inline void BinaryTree<T,V>::clear() {
		clearR(_root);


	}
	template<typename T, typename V>
	inline void BinaryTree<T,V>::push(const T& key, const V& value) {
		addElemR(key, value);
	}
	template<typename T, typename V>
	inline int BinaryTree<T,V>::getHeight() {
		return getHeightR(_root) - 1;
	}
	template<typename T, typename V>
	inline bool BinaryTree<T,V>::removeR(Node*& node, const T& key) {
		if (node == nullptr) return false;
		
		if (key > node->key) {
			bool result = removeR(node->right, key);
			Balance(node, node->left->key);
			return result;
		}
		else if (key < node->key) {
			bool result = removeR(node->left, key);
			Balance(node, node->right->key);
			return result;
		}
		else {
			if (node->left == nullptr && node->right == nullptr) {

				delete node;
				node = nullptr;
			}
			else if (node->left != nullptr) {

				Node* largestLeftChild = node->left;
				while (largestLeftChild->right->right != nullptr) {
					largestLeftChild = largestLeftChild->right;
				}
				node->value = largestLeftChild->right->value;
				node->key = largestLeftChild->right->key;
				delete largestLeftChild->right;
				largestLeftChild->right = nullptr;
			}
			else if (node->right != nullptr) {
				Node* right = node->right;
				delete node;
				node = right;
			}

			return true;
		}

	}
	template<typename T, typename V>
	inline bool BinaryTree<T, V>::count(const T& key) {
		return countR(key, _root);
	}
	
	template<typename T, typename V>
	inline bool BinaryTree<T, V>::remove(const T& key) {
		bool result = removeR(_root, key);
		return result;
	}

	// In Order
	template<typename T, typename V>
	inline void BinaryTree<T,V>::printIO() {
		inOrderPrint(_root);
	}
	template<typename T, typename V>
	inline void BinaryTree<T, V>::print()
	{
		//system("cls");
		printR("", _root, false);
		//system("pause");
	}

	template<typename T, typename V>
	inline V& BinaryTree<T, V>::find(const T& key) {
		
		if (lastFound != nullptr) {
			if (lastFound->key == key) return lastFound->key;
		}
		return findR(key, _root);
	}

	inline const char* dts::String::c_str() {
		return cstr;
	}

	inline dts::String::String() {
		cstr = nullptr;
		_size = 0;
	}

	inline dts::String::String(const string& s) {
		if (!s.empty()) {
			cstr = new char[s.size() + 1];
			strcpy(cstr, s.c_str());
		}
		else cstr = nullptr;

		_size = s.size();
	}

	inline dts::String::String(int size) {
		cstr = new char[size];
		cstr[0] = '\0'; // для strcat-совместимости
		_size = size;
	}

	inline dts::String::String(const String& s) {
		if (s.cstr != nullptr) {
			cstr = new char[strLen(s.cstr) + 1];
			strcpy(cstr, s.cstr);
		}
		else cstr = nullptr;

		_size = s._size;
	}

	inline dts::String::String(const char* cs) {
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

	inline dts::String::~String() {
		if (cstr != nullptr) {
			delete[]cstr;
			cstr = nullptr;
			_size = 0;
		}
	}

	inline int dts::String::size() const {
		return _size;
	}

	inline int dts::String::length() {
		return _size;
	}

	inline String& dts::String::append(const String& s) {
		char* newCStr = new char[_size + s._size + 1];
		if (cstr != nullptr) strcpy(newCStr, cstr);
		else {
			if (s.cstr != nullptr) strcpy(newCStr, s.cstr);
			cstr = newCStr;
			_size = _size + s._size;
			return *this;
		}
		if (s.cstr != nullptr) strcat(newCStr, s.cstr);
		if (cstr != nullptr) {
			delete[]cstr;
			cstr = nullptr;
		}
		cstr = newCStr;
		_size = _size + s._size;
		return *this;
	}

	inline String& dts::String::append(char s) {


		char* newCStr = new char[_size + 2];
		if (cstr != nullptr) strcpy(newCStr, cstr);
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

	inline String& dts::String::reverse() {
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

	inline String dts::StringBuilder::toString() const {
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
}
#endif