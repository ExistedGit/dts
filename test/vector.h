#pragma once
#include "dts.h"

namespace dts {
	// Вектор(динамический массив)
	template <typename Type>
	class Vector
	{
	private:
		Type* arr;
		int _size;
		int _capacity;

		void adjustCapacity(int newCap);
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


	};

}
namespace dts {
	template<typename Type>
	inline Vector<Type>::Vector() {
		
		_size = 0;
		_capacity = 4;
		arr = new Type[_capacity];
	}
	template<typename Type>
	inline Vector<Type>::Vector(const Vector& orig) {
		_size = orig._size;
		arr = new Type[orig._capacity];
		for (int i = 0; i < _size; i++) {
			arr[i] = orig.arr[i];
		}
		_capacity = orig._capacity;
	}
	template<typename Type>
	inline Vector<Type>::Vector(std::initializer_list<Type> _arr) : Vector() {
		adjustCapacity(_arr.size());
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
	inline void Vector<Type>::adjustCapacity(int newCap) {
		int oldCapacity = _capacity;
		if (newCap <= _capacity / 2) {
			while (newCap <= _capacity) _capacity /= 2;
		}
		else {
			while (newCap > _capacity) _capacity *= 2;
		}
		if (_capacity == oldCapacity) return;
		Type* oldArr = arr;
		arr = new Type[_capacity];
		for (int i = 0; i < _size; i++) {
			arr[i] = oldArr[i];
		}
		delete[]oldArr;
		oldArr = nullptr;
	}
	template<typename Type>
	inline void Vector<Type>::push_back(const Type& elem) {
		adjustCapacity(_size + 1);
		arr[_size++] = elem;
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
		try {
			if (index >= 0 && index < _size) return arr[index];
			else throw out_of_range("Вектор: неверный индекс");
		}
		catch (out_of_range err) {
			cerr << err.what();
		}
	}
	template<typename Type>
	inline bool Vector<Type>::remove(int index) {
		if (index >= 0 && index < _size) {
			adjustCapacity(_size - 1);

			if (index == -1) index = _size - 1;
			for (int i = index + 1; i < _size; i++) {
				arr[i - 1] = arr[i];
			}
			arr[_size] = Type();
			_size--;
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
	
	
}