#pragma once
#include "dts.h"

namespace dts {
	// Односвязный список
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

		template<typename T>
		friend List<T> toDoubleList(const linked_list<T>& ll);
		template<typename T>
		friend Vector<T> toArray(const linked_list<T>& ll);
	};
}

namespace dts {
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
}