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
	
	
}