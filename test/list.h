#pragma once
#include "dts.h"

namespace dts {
	// Односвязный список
	// Доступны два набора функций: итеративные и рекурсивные. По умолчанию используются итеративные. Чтобы включить второй набор, пропишите #define RECURSIVE_LL_FUNCTIONS
	template <typename T>
	class ForwardList {
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

		void addElemR(const T& elem, LinkedElement* linkedElem = nullptr);
		void addElemI(const T& elem);
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
		ForwardList();
		ForwardList(const std::initializer_list<T> il);
		ForwardList(const ForwardList& orig);


		ForwardList<T>& operator=(const ForwardList& orig) {
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

		~ForwardList();

		ForwardList* clear();

		// Процедурные оболочки рекурсивных функций
		ForwardList* push_back(const T& elem);

		ForwardList* push_front(const T& elem);
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

		int size() const;
		bool empty() const;

		template<typename T>
		friend void bubbleSort(ForwardList<T>& a);

		template<typename type>
		friend ostream& operator<<(ostream& os, ForwardList<type>& a);

		template<typename T>
		friend List<T> toDoubleList(const ForwardList<T>& ll);
		template<typename T>
		friend Vector<T> toArray(const ForwardList<T>& ll);
	};

	template<typename T, typename = enable_if_t<is_arithmetic_v<T>>>
	inline void bubbleSort(ForwardList<T>& a) { // Работает только с численными списками
		for (int i = 0; i < a._size; i++) {
			a.bubbleSortCycleR();
		}
		
	}
	template<typename type>
	ostream& operator<<(ostream& os, ForwardList<type>& a) {
		a.recursivePrint();
		return os;
	}

	// Двусвязный список
	template <typename T>
	class List {
	
	public:
		

		class Node {
		protected:
			T value;
			Node* next;
			Node* prev;
		public:
			Node() {
				value = T();
				next = nullptr;
				prev = nullptr;
			}
			Node(const T& _value, Node* _next = nullptr, Node* _prev = nullptr) {
				value = _value;
				next = _next;
				prev = _prev;
			}
			Node(nullptr_t np) {
				value = T();
				next = nullptr;
				prev = nullptr;
			}

			T& operator* () {
				return this->value;
			}
			//Node operator+(int index) {

			//	Node* linkedElem = this;
			//	for (int i = 0; i < index && linkedElem->next != nullptr; i++) {
			//		linkedElem = linkedElem->next;
			//	}
			//	return Node(linkedElem);
			//}
			//Node operator-(int index) {
			//	Node* linkedElem = this;
			//	for (int i = 0; i < index && linkedElem->prev != nullptr; i++) {
			//		linkedElem = linkedElem->prev;
			//	}
			//	return Node(linkedElem);
			//}
			//Node& operator+=(int index) {
			//	*this = *this + index;
			//	return *this;
			//}
			//Node& operator-=(int index) {
			//	*this = *this - index;
			//	return *this;
			//}

			//Node& operator++() {
			//	*this += 1;
			//	return *this;
			//}
			//Node& operator--() {
			//	*this -= 1;
			//	return *this;
			//}
			//Node operator++(int i) {
			//	Node tmp = *this;
			//	*this += 1;
			//	return tmp;
			//}
			//Node operator--(int i) {
			//	Node tmp = *this;
			//	*this -= 1;
			//	return tmp;
			//}

			//bool operator==(const Node& right) {
			//	return this == right this;
			//}
			//bool operator!=(const Node& right) {
			//	return this != right this;
			//}
			//bool operator<(const Node& right) {
			//	Node* it = this;
			//	while (it->next != nullptr) {
			//		it = it->next;
			//		if (it == right this) return true;
			//	}
			//	return false;
			//}
			//bool operator>(const Node& right) {
			//	Node* it = this;
			//	while (it->prev != nullptr) {
			//		it = it->prev;
			//		if (it == right this) return true;
			//	}
			//	return false;
			//}
			//bool operator<=(const Node& right) {
			//	return *this == right || *this < right;
			//}
			//bool operator>=(const Node& right) {
			//	return *this == right || *this > right;
			//}
			
			
			friend class List;
		};

		//class Iterator {
		//	Node* ptr;
		//public:
		//	Iterator(Node* ptr) {
		//		this->ptr = ptr;
		//	}
		//};
	protected:
		

		T& getElemFirst(int index);
		T& getElemLast(int index);

		void pushFront(const T& elem);

		void bubbleSortCycleR(Node* linkedElem = nullptr);
		void bubbleSortI();

		T popFirst(int index);
		T popLast(int index);

		int findLeftR(Node* linkedElem, const T& elem, int currIndex = 0);
		int findRightR(Node* linkedElem, const T& elem, int currIndex = 0, int lastFoundIndex = 0);

		Node* _first;
		Node* _last;
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

				_first = new Node(orig._first->value);
				Node* linkedElem = _first;
				Node* origLinkedElem = orig._first;
				while (origLinkedElem->next != nullptr) {
					linkedElem->next = new Node(origLinkedElem->next->value, nullptr, linkedElem);
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

		Node& end();
		Node& begin();

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
		friend ForwardList<T> toList(const List<T>& dll);
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

		Deque* push_front(const T& elem);
		Deque* push_back(const T& elem);

		T pop_front();
		T pop_back();
		typename List<T>::Node& begin();
		typename List<T>::Node& end();
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
		ForwardList<T> stack;
		
	public:
		Stack() {};
		Stack(initializer_list<T> il);

		Stack* push(const T& elem);
		T pop();
		T& peek() const;
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
		int count() const;
	};

	template<typename T>
	class PriorityQueue {
		class Node {
			T value;
			Node* next;
			Node* prev;
		public:
			int priority;
			Node() {
				value = T();
				next = nullptr;
				prev = nullptr;
				priority = 0;
			}
			Node(const T& _value, int _priority = 0, Node* _next = nullptr, Node* _prev = nullptr) {
				value = _value;
				next = _next;
				prev = _prev;
				priority = _priority;
			}
			T& operator*() {
				return value;
			}
			Node operator+(int index) {
				Node* linkedElem = this;
				for (int i = 0; i < index && linkedElem->next != nullptr; i++) {
					linkedElem = linkedElem->next;
				}
				return *linkedElem;
			}
			Node operator-(int index) {
				Node* linkedElem = this;
				for (int i = 0; i < index && linkedElem->prev != nullptr; i++) {
					linkedElem = linkedElem->prev;
				}
				return *linkedElem;
			}
			Node& operator+=(int index) {
				*this = *this + index;
				return *this;
			}
			Node& operator-=(int index) {
				*this = *this - index;
				return *this;
			}

			Node& operator++() {
				*this += 1;
				return *this;
			}
			Node& operator--() {
				*this -= 1;
				return *this;
			}
			Node operator++(int i) {
				Node tmp = *this;
				*this += 1;
				return tmp;
			}
			Node operator--(int i) {
				Node tmp = *this;
				*this -= 1;
				return tmp;
			}

			bool operator==(const Node& right) {
				return value == right.value && next == right.next && prev == right.prev;
			}
			bool operator!=(const Node& right) {
				return !(*this == right);
			}
			bool operator<(const Node& right) {
				Node* it = this;
				while (it->next != nullptr) {
					it = it->next;
					if (*it == right) return true;
				}
				return false;
			}
			bool operator>(const Node& right) {
				Node* it = this;
				while (it->prev != nullptr) {
					it = it->prev;
					if (*it == right) return true;
				}
				return false;
			}
			bool operator<=(const Node& right) {
				return *this == right || *this < right;
			}
			bool operator>=(const Node& right) {
				return *this == right || *this > right;
			}

			friend class PriorityQueue;
		};
	protected:
		Node* _first;
		Node* _last;

		int topPriority;
		Node* _top;

		void adjustTop(Node* it, int priority);
	public:
		PriorityQueue();
		PriorityQueue(const initializer_list<T> il);
		PriorityQueue(const PriorityQueue<T>& orig);

		void push(const T& elem, int priority);
		T pop();
		bool empty() const;
		Node top() const;
		T& last();
	};
	
}

namespace dts {
	
	template<typename T>
	inline List<T> toDoubleList(const ForwardList<T>& ll) {
		List<T> result;
		typename ForwardList<T>::Node node = ll._first;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline Vector<T> toArray(const ForwardList<T>& ll) {
		Vector<T> result;
		typename ForwardList<T>::Node node = ll._first;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline void List<T>::pushFront(const T& elem) {
		if (_first == nullptr) {
			_first = new Node(elem);
			_last = _first;
		}
		_first->prev = new Node(elem);
		_first = _first->prev;
	}
	template<typename T>
	inline T& List<T>::getElemLast(int index) { // нахождение с конца
		if (index < 0 || index >= _size) throw out_of_range("Неверный индекс связанного списка");

		Node* linkedElem = _last;
		for (int current = _size - 1; current != index; current--) {
			linkedElem = linkedElem->prev;
		}
		return linkedElem->value;
	}
	template<typename T>
	inline T& List<T>::getElemFirst(int index) { // нахождение с начала
		if (index < 0 || index >= _size) throw out_of_range("Неверный индекс связанного списка");

		Node* linkedElem = _first;
		for (int current = 0; current != index; current++) {
			linkedElem = linkedElem->next;
		}
		return linkedElem->value;
	}
	template<typename T>
	inline void List<T>::bubbleSortCycleR(Node* linkedElem) { // Метод, проводящий один цикл пузырьковой сортировки(повторяется нужное количество раз уже в bubbleSort()
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
		Node linkedElem = _first;
		for (int i = 0; i < _size; i++) {
			if (linkedElem->value > linkedElem->next->value) {
				swap(linkedElem->value, linkedElem->next->value);

			}
			linkedElem = linkedElem->next;
		}
	}
	template<typename T>
	inline T List<T>::popLast(int index) {
		Node* linkedElem = _first;
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
		Node* linkedElem = _first;
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
	inline int List<T>::findLeftR(Node* linkedElem, const T& elem, int currIndex) {
		if (linkedElem->value == elem) {
			return currIndex;
		}
		else {
			return findLeftR(linkedElem->next, elem, currIndex + 1);
		}
	}
	template<typename T>
	inline int List<T>::findRightR(Node* linkedElem, const T& elem, int currIndex, int lastFoundIndex) {
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

			_first = new Node(orig._first->value);
			Node* linkedElem = _first;
			Node* origLinkedElem = orig._first;
			while (origLinkedElem->next != nullptr) {
				linkedElem->next = new Node(origLinkedElem->next->value, nullptr, linkedElem);
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
			_last = new Node(elem);
			_first = _last;
		}
		else {
			Node* oldLast = _last;

			oldLast->next = new Node(elem, nullptr, oldLast);
			_last = oldLast->next;
		}
		_size++;

		return this;
	}
	template<typename T>
	inline List<T>* List<T>::push_front(const T& elem) {
		if (_first == nullptr) {
			_first = new Node(elem);
			_last = _first;
		}
		else {
			Node* oldFirst = _first;
			_first = new Node(elem, oldFirst);
			oldFirst->prev = _first;
		}
		_size++;
		return this;
	}
	template<typename T>
	inline T List<T>::pop_back() {
		if (_last == nullptr) throw runtime_error("Список пуст");

		T value = _last->value;
		Node* prev = _last->prev;
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
		Node* next = _first->next;
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
	inline typename List<T>::Node& List<T>::begin() {
		return *_first;
	}
	template<typename T>
	inline typename List<T>::Node& List<T>::end() {
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
	inline ForwardList<T> toList(const List<T>& dll) {
		ForwardList<T> result;
		typename List<T>::Node node = dll._first;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline Vector<T> toArray(const List<T>& dll) {
		Vector<T> result;
		
		typename List<T>::Node node = dll._first;
		while (node->next != nullptr) {
			result.push_back(node->value);
			node = node->next;
		}
		return result;
	}
	template<typename T>
	inline Deque<T>* Deque<T>::push_front(const T& elem) {
		deque.push_front(elem);
		return this;
	}
	template<typename T>
	inline Deque<T>* Deque<T>::push_back(const T& elem) {
		deque.push_back(elem);
		return this;
	}
	template<typename T>
	inline T Deque<T>::pop_front() {
		return deque.pop_front();

	}
	template<typename T>
	inline T Deque<T>::pop_back() {
		return deque.pop_back();
	}
	template<typename T>
	inline typename List<T>::Node& Deque<T>::begin() {
		return deque.begin();
	}
	template<typename T>
	inline typename List<T>::Node& Deque<T>::end() {
		return deque.end();
	}
	template<typename T>
	inline int Deque<T>::count() const {
		return deque.size();
	}
	template<typename T>
	inline Stack<T>::Stack(initializer_list<T> il) {
		while (count() != 0) pop();

		for (int i = 0; i < il.size(); i++) {
			stack.push_front(*(il.begin() + i));
		}
	}
	template<typename T>
	inline Stack<T>* Stack<T>::push(const T& elem) {
		stack.push_front(elem);
		return this;
	}
	template<typename T>
	inline T Stack<T>::pop() {
		if (stack.empty()) {
			throw runtime_error("Стек пуст!");
		}
		return stack.pop_front();
	}
	template<typename T>
	inline T& Stack<T>::peek() const {
		if (stack.empty()) {
			throw runtime_error("Стек пуст!");
		}
		return stack.first();
	}
	template<typename T>
	inline int Stack<T>::count() const {
		return stack.size();
	}
	template<typename T>
	inline Queue<T>* Queue<T>::enqueue(const T& elem) {
		queue.push_front(elem);
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
		return queue.pop_back();
	}

	template<typename T>
	inline int Queue<T>::count() const {
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
	inline ForwardList<Type> toList(const Vector<Type>& v) {
		ForwardList<Type> result;
		for (int i = 0; i < v.size(); i++) {
			result.push_back(v[i]);
		}
		return result;
	}
}

namespace dts {
	template<typename T>
	inline void ForwardList<T>::recursivePrint(LinkedElement* l) { // Рекурсивная начинка вывода списка
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
	inline void ForwardList<T>::iterativePrint() {
		if (_first == nullptr) return;
		LinkedElement* l = _first;
		for (int i = 0; i < _size; i++) {
			cout << l->value << " ";
			l = l->next;
		}
	}
	template<typename T>
	inline void ForwardList<T>::addElemR(const T& elem, LinkedElement* linkedElem) { // Рекурсивная начинка добавления объекта в список
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
	inline void ForwardList<T>::addElemI(const T& elem) { // Итеративная начинка добавления объекта в список
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
	inline T& ForwardList<T>::getElemR(int index, int current, LinkedElement* linkedElem) { // Рекурсивная начинка нахождения n-ного объекта списка
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
	inline T& ForwardList<T>::getElemI(int index) { // Итеративная начинка нахождения n-ного объекта списка
		if (index < 0 || index >= _size) throw out_of_range("Неверный индекс связанного списка");

		LinkedElement* linkedElem = _first;
		for (int current = 0; current != index; current++) {
			linkedElem = linkedElem->next;
		}
		return linkedElem->value;
	}
	template<typename T>
	inline T& ForwardList<T>::pop_backR(LinkedElement* linkedElem) { // Рекурсивная начинка удаления последнего объекта списка
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
	inline T& ForwardList<T>::pop_backI() { // Итеративная начинка удаления последнего объекта списка
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
	inline void ForwardList<T>::bubbleSortCycleR(LinkedElement* linkedElem) { // Метод, проводящий один цикл пузырьковой сортировки(повторяется нужное количество раз уже в bubbleSort()
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
	inline void ForwardList<T>::bubbleSortI() {
		LinkedElement linkedElem = _first;
		for (int i = 0; i < _size; i++) {
			if (linkedElem->value > linkedElem->next->value) {
				swap(linkedElem->value, linkedElem->next->value);

			}
			linkedElem = linkedElem->next;
		}
	}
	template<typename T>
	inline T ForwardList<T>::popR(int index, LinkedElement* linkedElem, int current) {
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
	inline T ForwardList<T>::popI(int index) {
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
	inline int ForwardList<T>::findLeftR(LinkedElement* linkedElem, const T& elem, int currIndex) {
		if (linkedElem == nullptr) return -1;

		if (linkedElem->value == elem) {
			return currIndex;
		}
		else {
			return findLeftR(linkedElem->next, elem, currIndex + 1);
		}
	}
	template<typename T>
	inline int ForwardList<T>::findRightR(LinkedElement* linkedElem, const T& elem, int currIndex, int lastFoundIndex) {
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
	inline int ForwardList<T>::find(const T& elem, bool right) {
		if (!right)return findLeftR(_first, elem);
		else return findRightR(_first, elem);
	}
	template<typename T>
	inline ForwardList<T>::ForwardList() {
		_first = nullptr;
		_size = 0;
	}
	template<typename T>
	inline ForwardList<T>::ForwardList(const std::initializer_list<T> il) : ForwardList() {
		for (int i = 0; i < il.size(); i++) {
			push_back(*(il.begin() + i));
		}
		_size = il.size();
	}
	template<typename T>
	inline ForwardList<T>::ForwardList(const ForwardList& orig) {
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
	inline ForwardList<T>::~ForwardList() {
		clear();
	}
	template<typename T>
	inline ForwardList<T>* ForwardList<T>::clear() {
		while (_size != 0) pop_front();
		return this;
	}

	// Процедурные оболочки рекурсивных функций
	template<typename T>
	inline ForwardList<T>* ForwardList<T>::push_back(const T& elem) {
#ifdef RECURSIVE_LL_FUNCTIONS
		addElemR(elem);
#else
		addElemI(elem);
#endif
		return this;
	}
	template<typename T>
	inline ForwardList<T>* ForwardList<T>::push_front(const T& elem) {
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
	inline T ForwardList<T>::pop_front() {
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
	inline T ForwardList<T>::pop_back() {
#ifdef RECURSIVE_LL_FUNCTIONS
		return pop_backR();
#else 
		return pop_backI();
#endif
	}
	template<typename T>
	inline T ForwardList<T>::pop(int index) {
#ifdef RECURSIVE_LL_FUNCTIONS
		return popR(index);
#else
		return popI(index);
#endif
	}
	template<typename T>
	inline void ForwardList<T>::print() {
#ifdef RECURSIVE_LL_FUNCTIONS
		recursivePrint();
#else
		iterativePrint();
#endif
		cout << endl;
	}
	template<typename T>
	inline T& ForwardList<T>::first() {
		return _first->value;
	}
	template<typename T>
	inline T& ForwardList<T>::last() {
		return (*this)[_size - 1];
	}
	template<typename T>
	inline T& ForwardList<T>::at(int index) {
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
	inline bool ForwardList<T>::empty() const {
		return _first == nullptr;
	}
	template<typename T>
	inline int ForwardList<T>::size() const {
		return _size;
	}

	template<typename T>
	inline void PriorityQueue<T>::adjustTop(Node* it, int priority) {
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
		_first = new Node(orig._first->value, orig._first->priority);
		_last = _first;
		for (auto i = orig._first + 1; i < orig._last; i++) {
			_last->next = new Node(i.value, i.priority, _last);
			_last = _last->next;
		}
	}
	template<typename T>
	inline void PriorityQueue<T>::push(const T& elem, int priority) {
		if (_first == nullptr) {
			_first = new Node(elem, priority);
			_last = _first;
			adjustTop(_first, priority);
			return;
		}
		Node* it = _first;
		while (it->next != nullptr && it->priority < priority) {
			it = it->next;
		}
		if (priority > it->priority) {
			Node* tmp = it->next;
			it->next = new Node(elem, priority, tmp, it);
			if (tmp != nullptr) tmp->prev = it->next;

			adjustTop(it->next, priority);
		}
		else {
			Node* tmp = it->prev;
			it->prev = new Node(elem, priority, it, tmp);
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
	inline T PriorityQueue<T>::pop() {
		try {
			if (_last == nullptr) throw runtime_error("Очередь с приоритетом пуста(dequeue).");

			if (_first == _last) {
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
	inline typename PriorityQueue<T>::Node PriorityQueue<T>::top() const {
		try {
			if (!empty()) return _top;
			else throw runtime_error("Очередь с приоритетом пуста!");
		}
		catch (runtime_error re) {
			cerr << re.what();
		}
	}
	template<typename T>
	inline T& PriorityQueue<T>::last() {
		return **_last;
	}
}