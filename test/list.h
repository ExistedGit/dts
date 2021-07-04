#pragma once
#include "dts.h"

namespace dts {
	

	template<typename T, typename = enable_if_t<is_arithmetic_v<T>>>
	inline void bubbleSort(linked_list<T>& a) { // Работает только с численными списками
		for (int i = 0; i < a._size; i++) {
			a.bubbleSortCycleR();
		}
		
	}
	template<typename type>
	ostream& operator<<(ostream& os, linked_list<type>& a) {
		a.recursivePrint();
		return os;
	}

	// Двусвязный список
	template <typename T>
	class List {
	
	public:
		

		class Iterator {
		protected:
			T value;
			Iterator* next;
			Iterator* prev;
		public:
			Iterator() {
				value = T();
				next = nullptr;
				prev = nullptr;
			}
			Iterator(const T& _value, Iterator* _next = nullptr, Iterator* _prev = nullptr) {
				value = _value;
				next = _next;
				prev = _prev;
			}
			Iterator(nullptr_t np) {
				value = T();
				next = nullptr;
				prev = nullptr;
			}

			T& operator* () {
				return value;
			}
			Iterator operator+(int index) {
				Iterator* linkedElem = this;
				for (int i = 0; i < index && linkedElem->next != nullptr; i++) {
					linkedElem = linkedElem->next;
				}
				return *linkedElem;
			}
			Iterator operator-(int index) {
				Iterator* linkedElem = this;
				for (int i = 0; i < index && linkedElem->prev != nullptr; i++) {
					linkedElem = linkedElem->prev;
				}
				return *linkedElem;
			}
			Iterator& operator+=(int index) {
				*this = *this + index;
				return *this;
			}
			Iterator& operator-=(int index) {
				*this = *this - index;
				return *this;
			}
			
			Iterator& operator++() {
				*this += 1;
				return *this;
			}
			Iterator& operator--() {
				*this -= 1;
				return *this;
			}
			Iterator operator++(int i) {
				Iterator tmp = *this;
				*this += 1;
				return tmp;
			}
			Iterator operator--(int i) {
				Iterator tmp = *this;
				*this -= 1;
				return tmp;
			}

			bool operator==(const Iterator& right) {
				return value == right.value && next == right.next && prev == right.prev;
			}
			bool operator!=(const Iterator& right) {
				return !(*this==right);
			}
			bool operator<(const Iterator& right) {
				Iterator* it = this;
				while (it->next != nullptr) {
					it = it->next;
					if (*it == right) return true;
				}
				return false;
			}
			bool operator>(const Iterator& right) {
				Iterator* it = this;
				while (it->prev != nullptr) {
					it = it->prev;
					if (*it == right) return true;
				}
				return false;
			}
			bool operator<=(const Iterator& right) {
				return *this == right || *this < right;
			}
			bool operator>=(const Iterator& right) {
				return *this == right || *this > right;
			}
			
			friend class List;
		};
		
	protected:
		
		void pushFront(const T& elem);

		T& getElemFirst(int index);
		T& getElemLast(int index);
		

		void bubbleSortCycleR(Iterator* linkedElem = nullptr);
		void bubbleSortI();

		T popFirst(int index);
		T popLast(int index);

		int findLeftR(Iterator* linkedElem, const T& elem, int currIndex = 0);
		int findRightR(Iterator* linkedElem, const T& elem, int currIndex = 0, int lastFoundIndex = 0);

		Iterator* _first;
		Iterator* _last;
		int _size;
	public:
		int find(const T& elem, bool right = false);

		List();
		List(const std::initializer_list<T> il);

		List(const List<T>& orig);


		List<T>& operator=(const List& orig) {
			if (_size != 0) clear();

			
			if (orig._first == nullptr) {
				_first = nullptr;
				_last = _first;
				_size = 0;
			}
			else {

				_first = new Iterator(orig._first->value);
				Iterator* linkedElem = _first;
				Iterator* origLinkedElem = orig._first;
				while (origLinkedElem->next != nullptr) {
					linkedElem->next = new Iterator(origLinkedElem->next->value, nullptr, linkedElem);
					linkedElem = linkedElem->next;
					origLinkedElem = origLinkedElem->next;
				}
				_last = linkedElem;
				_size = orig._size;
			}
			return *this;
		}

		~List();

		List* clear();

		List* push_back(const T& elem);

		List* push_front(const T& elem);
		T pop_back();
		T pop_front();

		T pop(int index);

		void print();

		Iterator& end();
		Iterator& begin();

		T& at(int index);

		T& operator[](int index) {
			return at(index);
		}

		int size() const;

		template<typename T>
		friend void bubbleSort(List<T>& a);

		template<typename type>
		friend ostream& operator<<(ostream& os, List<type>& a);

		
		template<typename T>
		friend Vector<T> toArray(const List<T>& dll);
		template<typename T>
		friend linked_list<T> toList(const List<T>& dll);
	};

	template<typename type>
	inline ostream& operator<<(ostream& os, List<type>& a) {
		a.recursivePrint();
		return os;
	}

	// Двустороння очередь
	template <typename T>
	class Deque {
	private:
		List<T> deque;
	public:
		Deque() {};

		Deque* enqueueFirst(const T& elem);
		Deque* enqueueLast(const T& elem);

		T dequeueFirst();
		T dequeueLast();
		typename List<T>::Iterator begin();
		typename List<T>::Iterator end();
		int count() const;
		T& operator[](unsigned int index) const {
			return deque.at(index);
		}

		
		friend class Queue<T>;
		friend class Stack<T>;
	};

	// Стек
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

	// Очередь
	template <typename T>
	class Queue {
	private:
		Deque<T> queue;
	public:
		Queue() {};
		Queue(const initializer_list<T>& il) {
			for (int i = 0; i < il.size(); i++) {
				enqueue(*(il.begin()+i));
			}
		};

		Queue* enqueue(const T& elem);
		T dequeue();
		T& first();
		T& last();
		int count()
	};

	template<typename T>
	class PriorityQueue{
	
		class Iterator {
			T value;
			Iterator* next;
			Iterator* prev;
		public:
			int priority;
			Iterator() {
				value = T();
				next = nullptr;
				prev = nullptr;
				priority = 0;
			}
			Iterator(const T& _value, int _priority = 0, Iterator* _next = nullptr, Iterator* _prev = nullptr) {
				value = _value;
				next = _next;
				prev = _prev;
				priority = _priority;
			}
			T& operator*() {
				return value;
			}
			Iterator operator+(int index) {
				Iterator* linkedElem = this;
				for (int i = 0; i < index && linkedElem->next != nullptr; i++) {
					linkedElem = linkedElem->next;
				}
				return *linkedElem;
			}
			Iterator operator-(int index) {
				Iterator* linkedElem = this;
				for (int i = 0; i < index && linkedElem->prev != nullptr; i++) {
					linkedElem = linkedElem->prev;
				}
				return *linkedElem;
			}
			Iterator& operator+=(int index) {
				*this = *this + index;
				return *this;
			}
			Iterator& operator-=(int index) {
				*this = *this - index;
				return *this;
			}

			Iterator& operator++() {
				*this += 1;
				return *this;
			}
			Iterator& operator--() {
				*this -= 1;
				return *this;
			}
			Iterator operator++(int i) {
				Iterator tmp = *this;
				*this += 1;
				return tmp;
			}
			Iterator operator--(int i) {
				Iterator tmp = *this;
				*this -= 1;
				return tmp;
			}

			bool operator==(const Iterator& right) {
				return value == right.value && next == right.next && prev == right.prev;
			}
			bool operator!=(const Iterator& right) {
				return !(*this == right);
			}
			bool operator<(const Iterator& right) {
				Iterator* it = this;
				while (it->next != nullptr) {
					it = it->next;
					if (*it == right) return true;
				}
				return false;
			}
			bool operator>(const Iterator& right) {
				Iterator* it = this;
				while (it->prev != nullptr) {
					it = it->prev;
					if (*it == right) return true;
				}
				return false;
			}
			bool operator<=(const Iterator& right) {
				return *this == right || *this < right;
			}
			bool operator>=(const Iterator& right) {
				return *this == right || *this > right;
			}

			friend class PriorityQueue;
		};
	protected:
		Iterator* _first;
		Iterator* _last;

		int topPriority;
		Iterator* _top;

		void adjustTop(Iterator* it, int priority);
	public:
		PriorityQueue();
		PriorityQueue(const initializer_list<T> il);
		PriorityQueue(const PriorityQueue<T>& orig);

		void push(const T& elem, int priority);
		T pop();
		bool empty() const;
		Iterator top();
		T& last() {
			return **_last;
		}
	};

	template<typename T>
	class PriorityQueue{
	
		class Iterator {
			T value;
			Iterator* next;
			Iterator* prev;
		public:
			int priority;
			Iterator() {
				value = T();
				next = nullptr;
				prev = nullptr;
				priority = 0;
			}
			Iterator(const T& _value, int _priority = 0, Iterator* _next = nullptr, Iterator* _prev = nullptr) {
				value = _value;
				next = _next;
				prev = _prev;
				priority = _priority;
			}
			T& operator*() {
				return value;
			}
			Iterator operator+(int index) {
				Iterator* linkedElem = this;
				for (int i = 0; i < index && linkedElem->next != nullptr; i++) {
					linkedElem = linkedElem->next;
				}
				return *linkedElem;
			}
			Iterator operator-(int index) {
				Iterator* linkedElem = this;
				for (int i = 0; i < index && linkedElem->prev != nullptr; i++) {
					linkedElem = linkedElem->prev;
				}
				return *linkedElem;
			}
			Iterator& operator+=(int index) {
				*this = *this + index;
				return *this;
			}
			Iterator& operator-=(int index) {
				*this = *this - index;
				return *this;
			}

			Iterator& operator++() {
				*this += 1;
				return *this;
			}
			Iterator& operator--() {
				*this -= 1;
				return *this;
			}
			Iterator operator++(int i) {
				Iterator tmp = *this;
				*this += 1;
				return tmp;
			}
			Iterator operator--(int i) {
				Iterator tmp = *this;
				*this -= 1;
				return tmp;
			}

			bool operator==(const Iterator& right) {
				return value == right.value && next == right.next && prev == right.prev;
			}
			bool operator!=(const Iterator& right) {
				return !(*this == right);
			}
			bool operator<(const Iterator& right) {
				Iterator* it = this;
				while (it->next != nullptr) {
					it = it->next;
					if (*it == right) return true;
				}
				return false;
			}
			bool operator>(const Iterator& right) {
				Iterator* it = this;
				while (it->prev != nullptr) {
					it = it->prev;
					if (*it == right) return true;
				}
				return false;
			}
			bool operator<=(const Iterator& right) {
				return *this == right || *this < right;
			}
			bool operator>=(const Iterator& right) {
				return *this == right || *this > right;
			}

			friend class PriorityQueue;
		};
	protected:
		Iterator* _first;
		Iterator* _last;

		int topPriority;
		Iterator* _top;

		void adjustTop(Iterator* it, int priority);
	public:
		PriorityQueue();
		PriorityQueue(const initializer_list<T> il);
		PriorityQueue(const PriorityQueue<T>& orig);

		void push(const T& elem, int priority);
		T pop();
		bool empty() const;
		Iterator begin();
		Iterator end();
		Iterator top();
	};
	template<typename T>
	inline void PriorityQueue<T>::adjustTop(Iterator* it, int priority) {
		if (it == nullptr) return;
		if (priority > topPriority) {
			topPriority = priority;
			_top = it;
		}
	}
	template<typename T>
	inline PriorityQueue<T>::PriorityQueue() {
		_first = nullptr;
		_last = _first;
		topPriority = 0;
		_top = nullptr;
	}
	template<typename T>
	inline PriorityQueue<T>::PriorityQueue(const initializer_list<T> il) {
		for (auto i = il.begin(); i < il.end(); i++) {
			push(*i, 0);
		}
	}
	template<typename T>
	inline PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& orig) {
		_first = new Iterator(orig._first->value, orig._first->priority);
		_last = _first;
		for (auto i = orig._first + 1; i < orig._last; i++) {
			_last->next = new Iterator(i.value, i.priority, _last);
			_last = _last->next;
		}
	}
	template<typename T>
	inline void PriorityQueue<T>::push(const T& elem, int priority) {
		if (_first == nullptr) {
			_first = new Iterator(elem, priority);
			_last = _first;
			adjustTop(_first, priority);
			return;
		}
		Iterator* it = _first;
		while (it->next != nullptr && it->priority < priority) {
			it = it->next;
		}
		if (priority > it->priority) {
			Iterator* tmp = it->next;
			it->next = new Iterator(elem, priority, tmp, it );
			if (tmp != nullptr) tmp->prev = it->next;

			
			adjustTop(it->next, priority);
		}
		else {
			Iterator* tmp = it->prev;
			it->prev = new Iterator(elem, priority, it, tmp);
			if (tmp != nullptr) tmp->next = it->prev;

			adjustTop(it->prev, priority);
		}
		if (_last->next != nullptr)_last = _last->next;
		if (_first->prev != nullptr) _first = _first->prev;
	}
	template<typename T>
	inline bool PriorityQueue<T>::empty() const {
		return _first == nullptr;
	}
	template<typename T>
	inline typename PriorityQueue<T>::Iterator PriorityQueue<T>::begin() {
		return *_first;
	}
	template<typename T>
	inline typename PriorityQueue<T>::Iterator PriorityQueue<T>::end() {
		return *_last;
	}
	template<typename T>
	inline T PriorityQueue<T>::pop() {
		try {
			if (_last == nullptr) throw runtime_error("Очередь с приоритетом пуста(dequeue).");

			if(_first == _last){
				T value = _first->value;
				delete _first;
				_first = nullptr;
				_last = _first;
				return value;
			}

			T value = _last->value;
			_last = _last->prev;
			delete _last->next;
			_last->next = nullptr;
			
			_top = _last;
			topPriority = _top->priority;

			return value;
		}
		catch (runtime_error re) {
			cout << re.what();
		}
	}
	template<typename T>
	inline typename PriorityQueue<T>::Iterator PriorityQueue<T>::top() {
		try {
			if (!empty()) return _top;
			else throw runtime_error("Очередь с приоритетом пуста!");
		}
		catch (runtime_error re) {
			cerr << re.what();
		}
	}
}

namespace dts {
	
	template<typename T>
	inline List<T> toDoubleList(const linked_list<T>& ll) {
		List<T> result;
		typename linked_list<T>::Iterator node = ll._first;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline Vector<T> toArray(const linked_list<T>& ll) {
		Vector<T> result;
		typename linked_list<T>::Iterator node = ll._first;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline void List<T>::pushFront(const T& elem) {
		if (_first == nullptr) {
			_first = new Iterator(elem);
			_last = _first;
		}
		_first->prev = new Iterator(elem);
		_first = _first->prev;
	}
	template<typename T>
	inline T& List<T>::getElemLast(int index) { // нахождение с конца
		if (index < 0 || index >= _size) throw out_of_range("Неверный индекс связанного списка");

		Iterator* linkedElem = _last;
		for (int current = _size - 1; current != index; current--) {
			linkedElem = linkedElem->prev;
		}
		return linkedElem->value;
	}
	template<typename T>
	inline T& List<T>::getElemFirst(int index) { // нахождение с начала
		if (index < 0 || index >= _size) throw out_of_range("Неверный индекс связанного списка");

		Iterator* linkedElem = _first;
		for (int current = 0; current != index; current++) {
			linkedElem = linkedElem->next;
		}
		return linkedElem->value;
	}
	template<typename T>
	inline void List<T>::bubbleSortCycleR(Iterator* linkedElem) { // Метод, проводящий один цикл пузырьковой сортировки(повторяется нужное количество раз уже в bubbleSort()
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
	inline void List<T>::bubbleSortI() {
		Iterator linkedElem = _first;
		for (int i = 0; i < _size; i++) {
			if (linkedElem->value > linkedElem->next->value) {
				swap(linkedElem->value, linkedElem->next->value);

			}
			linkedElem = linkedElem->next;
		}
	}
	template<typename T>
	inline T List<T>::popLast(int index) {
		Iterator* linkedElem = _first;
		for (int curr = _size - 1; curr != index; curr--) {
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
	inline T List<T>::popFirst(int index) {
		Iterator* linkedElem = _first;
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
	inline int List<T>::findLeftR(Iterator* linkedElem, const T& elem, int currIndex) {
		if (linkedElem->value == elem) {
			return currIndex;
		}
		else {
			return findLeftR(linkedElem->next, elem, currIndex + 1);
		}
	}
	template<typename T>
	inline int List<T>::findRightR(Iterator* linkedElem, const T& elem, int currIndex, int lastFoundIndex) {
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
	inline int List<T>::find(const T& elem, bool right) {
		if (!right)return findLeftR(_first, elem);
		else return findRightR(_first, elem);
	}
	template<typename T>
	inline List<T>::List() {
		_first = nullptr;
		_last = nullptr;
		_size = 0;
	}
	template<typename T>
	inline List<T>::List(const std::initializer_list<T> il) : List() {
		for (int i = 0; i < il.size(); i++) {
			push_back(*(il.begin() + i));
		}
		_size = il.size();
	}
	template<typename T>
	inline List<T>::List(const List& orig) {
		//if (_size != 0) clear();

		if (orig._first == nullptr) {
			_first = nullptr;
			_last = _first;
			_size = 0;
		}
		else {

			_first = new Iterator(orig._first->value);
			Iterator* linkedElem = _first;
			Iterator* origLinkedElem = orig._first;
			while (origLinkedElem->next != nullptr) {
				linkedElem->next = new Iterator(origLinkedElem->next->value, nullptr, linkedElem);
				linkedElem = linkedElem->next;
				origLinkedElem = origLinkedElem->next;
			}
			_last = linkedElem;
			_size = orig._size;
		}
	}
	template<typename T>
	inline List<T>::~List() {
		clear();
	}
	template<typename T>
	inline List<T>* List<T>::clear() {
		while (_size != 0) pop_front();
		return this;
	}

	// Процедурные оболочки рекурсивных функций
	template<typename T>
	inline List<T>* List<T>::push_back(const T& elem) {

		if (_last == nullptr) {
			_last = new Iterator(elem);
			_first = _last;
		}
		else {
			Iterator* oldLast = _last;

			oldLast->next = new Iterator(elem, nullptr, oldLast);
			_last = oldLast->next;
		}
		_size++;

		return this;
	}
	template<typename T>
	inline List<T>* List<T>::push_front(const T& elem) {
		if (_first == nullptr) {
			_first = new Iterator(elem);
			_last = _first;
		}
		else {
			Iterator* oldFirst = _first;
			_first = new Iterator(elem, oldFirst);
			oldFirst->prev = _first;
		}
		_size++;
		return this;
	}
	template<typename T>
	inline T List<T>::pop_back() {
		if (_last == nullptr) throw runtime_error("Список пуст");

		T value = _last->value;
		Iterator* prev = _last->prev;
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
	inline T List<T>::pop_front() {
		if (_first == nullptr) throw runtime_error("Список пуст");
		T value = _first->value;
		Iterator* next = _first->next;
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
	inline T List<T>::pop(int index) {
		if (index == 0) {
			return pop_front();
		}
		else if (index == _size - 1) {
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
	inline void List<T>::print() {

		for (auto i = this->begin(); i != this->end(); ++i) {
			cout << *i << " ";
		}
		cout << *this->end();
		cout << endl;
	}
	template<typename T>
	inline typename List<T>::Iterator& List<T>::begin() {
		return *_first;
	}
	template<typename T>
	inline typename List<T>::Iterator& List<T>::end() {
		return *_last;
	}
	template<typename T>
	inline T& List<T>::at(int index) {
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
	inline int List<T>::size() const {
		return _size;
	}
	template<typename T>
	inline linked_list<T> toList(const List<T>& dll) {
		linked_list<T> result;
		typename List<T>::Iterator node = dll._first;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline Vector<T> toArray(const List<T>& dll) {
		Vector<T> result;
		
		typename List<T>::Iterator node = dll._first;
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
	inline typename List<T>::Iterator Deque<T>::begin() {
		return deque.begin();
	}
	template<typename T>
	inline typename List<T>::Iterator Deque<T>::end() {
		return deque.end();
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
		return *queue.begin();
	}
	template <typename T>
	inline T& Queue<T>::last() {
		return *queue.end();
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
	inline List<Type> toDoubleList(const Vector<Type>& v) {
		List<Type> result;
		for (int i = 0; i < v.size(); i++) {
			result.push_back(v[i]);
		}
		return result;
	}

	template<typename Type>
	inline linked_list<Type> toList(const Vector<Type>& v) {
		linked_list<Type> result;
		for (int i = 0; i < v.size(); i++) {
			result.push_back(v[i]);
		}
		return result;
	}
}