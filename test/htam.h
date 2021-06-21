

#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <random>

// как math, только htam
namespace htam {
	template <typename T, typename = enable_if_t<is_arithmetic_v<T>>>
	class matrix
	{
		// между нами: тут на все случаи жизни методы
		// мне Андрей подсказывает, что добавлять
	private:
		T** _matrix;
		int _row, _col;
	public:
		matrix() {
			_matrix = nullptr;
			_row = 0, _col = 0;
		}
		matrix(int row, int col) {
			_matrix = new T * [row];
			for (int i = 0; i < row; i++) {
				_matrix[i] = new T[col];
				for (int j = 0; j < col; j++) {
					_matrix[i][j] = 0;
				}
			}
			_row = row;
			_col = col;
		}
		matrix(const matrix<T>& orig) : matrix() {
			_matrix = new T * [orig._row];
			for (int i = 0; i < orig._row; i++) {
				_matrix[i] = new T[orig._col];
				for (int j = 0; j < orig._col; j++) {
					_matrix[i][j] = orig._matrix[i][j];
				}
			}
			_row = orig._row;
			_col = orig._col;
		}

		matrix<T>& operator=(const matrix<T>& orig) {
			_matrix = new T * [orig._row];
			for (int i = 0; i < orig._row; i++) {
				_matrix[i] = new T[orig._col];
				for (int j = 0; j < orig._col; j++) {
					_matrix[i][j] = orig._matrix[i][j];
				}
			}//
			_row = orig._row;
			_col = orig._col;
			return *this;
		}

		void deleteMatrix(bool leaveFields = false) {
			for (int i = 0; i < _row; i++) {
				delete[]_matrix[i];
			}
			delete[]_matrix;
			_matrix = nullptr;
			if (!leaveFields) {
				_row = 0;
				_col = 0;
			}
		}

		T* operator[](int i) const {
			if (i >= 0 && i < _row) return _matrix[i];
		}
		void fillRandom(T min = 0, T max = 10) {
			for (int i = 0; i < _row; i++) {
				for (int j = 0; j < _col; j++) {
					std::random_device rd;
					std::mt19937 mt(rd());
					uniform_real_distribution<double> distribution(min, max);
					_matrix[i][j] = distribution(mt);
				}
			}
		};

		void addRow(const T*& newRow, int index = -1) {
			if (index == -1) index = _row;

			T** newMatrix = new T * [++_row];
			int shift = 0;
			for (int i = 0; i < _row; i++) {
				if (i == index) {
					newMatrix[index] = new T[_col];
					for (int j = 0; j < _col; j++) {
						newMatrix[index][j] = newRow[j];
					}
					shift = 1;
				}
				newMatrix[i + shift] = _matrix[i];
			}
		}
		// Добавить строку в матрицу с использованием списка инициализации
		void addRow(initializer_list<T> il, int index = -1) {
			if (index == -1) index = _row;

			T** newMatrix = new T * [++_row];
			int shift = 0;
			for (int i = 0; i < _row; i++) {
				if (i == index) {
					newMatrix[index] = new T[_col];
					for (int j = 0; j < _col; j++) {
						newMatrix[index][j] = *(il.begin() + j);
					}
					shift = 1;
					continue;
				}
				newMatrix[i] = _matrix[i - shift];
			}


			_matrix = newMatrix;
		}

		void addCol(const T*& newCol, int index = -1) {
			if (index == -1) index = _col;

			for (int i = 0; i < _row++; i++) {
				T* newRow = new T[_col + 1];
				int shift = 0;
				for (int j = 0; j < _col + 1; j++) {
					if (j == index) {
						newRow[index] = newCol[i];

						continue;
					}
					newRow[j] = _matrix[i][j - shift];
				}
				delete[]_matrix[i];
				_matrix[i] = newRow;
			}
			_col++;
		}
		void addCol(initializer_list<T> il, int index = -1) {
			if (index == -1) index = _col;

			for (int i = 0; i < _row; i++) {
				T* newRow = new T[_col + 1];
				int shift = 0;
				for (int j = 0; j < _col + 1; j++) {
					if (j == index) {
						newRow[index] = *(il.begin() + i);
						shift = 1;
						continue;
					}
					newRow[j] = _matrix[i][j - shift];
				}
				delete[]_matrix[i];
				_matrix[i] = newRow;
			}
			_col++;
		}

		void removeRow(int index = -1) {
			if (index == -1) index = _row - 1;
			if (index >= 0 && index < _row) {
				delete[]_matrix[index];
				T** newMatrix = new T * [--_row];
				int shift = 0;
				for (int i = 0; i < _row; i++) {
					if (i == index) {
						shift = 1;
					}
					newMatrix[i] = _matrix[i + shift];
				}
				deleteMatrix(true);
				_matrix = newMatrix;
			}
		}

		void removeCol(int index = -1) {
			if (index == -1) index = _col - 1;
			if (index >= 0 && index < _col) {
				for (int i = 0; i < _row; i++) {
					T* newRow = new T[_col - 1];
					int shift = 0;
					for (int j = 0; j < _col - 1; j++) {
						if (j == index) {
							shift = 1;
						}
						newRow[j] = _matrix[i][j + shift];
					}
					delete[]_matrix[i];
					_matrix[i] = newRow;
				}
			}
			--_col;
		}

		matrix<T>& sort() {
			T* matrixArray = new T[_row * _col];
			for (int i = 0; i < _row; i++) {
				for (int j = 0; j < _col; j++) {
					matrixArray[i * _col + j] = _matrix[i][j];
				}
			}
			quickSort(matrixArray, 0, _row * _col - 1);

			deleteMatrix(true);
			_matrix = new T * [_row];
			for (int i = 0; i < _row; i++) {
				_matrix[i] = new T[_col];
				for (int j = 0; j < _col; j++) {
					_matrix[i][j] = matrixArray[i * _col + j];
				}
			}
			return *this;
		}

		T maxElem() {
			T max = _matrix[0][0];
			for (int i = 0; i < _row; i++) {
				for (int j = 0; j < _col; j++) {
					if (_matrix[i][j] > max) max = _matrix[i][j];
				}
			}
			return max;
		}
		T minElem() {
			T min = _matrix[0][0];
			for (int i = 0; i < _row; i++) {
				for (int j = 0; j < _col; j++) {
					if (_matrix[i][j] < min) min = _matrix[i][j];
				}
			}
			return min;
		}

		void transpose() {
			T** newMatrix = new T * [_col];
			for(int i =0; i < _col;i++)
				newMatrix[i] = new T[_row];

			for (int i = 0; i < _row; i++) {
				for (int j = 0; j < _col; j++) {
					newMatrix[j][i] = _matrix[i][j];
				}
			}
			
			deleteMatrix(true);
			swap(_row, _col);
			_matrix = newMatrix;
		}

		template <typename T>
		friend ostream& operator<<(ostream& os, matrix<T> m);

		template <typename T>
		friend istream& operator>>(istream& is, matrix<T>& m);

		matrix<T> operator+(matrix<T> m) {

			try {
				if (_row == m._row && _col == m._col) {
					matrix<T> result(_row, _col);
					for (int i = 0; i < _row; i++) {
						for (int j = 0; j < _col; j++) {
							result[i][j] = _matrix[i][j] + m[i][j];
						}
					}
					return result;
				}
				else throw invalid_argument("Матрицы разных размеров!");
			}
			catch (invalid_argument err) {
				cerr << err.what();
			}
		}

		matrix<T> operator-(matrix<T> m) {

			try {
				if (_row == m._row && _col == m._col) {
					matrix<T> result(_row, _col);
					for (int i = 0; i < _row; i++) {
						for (int j = 0; j < _col; j++) {
							result[i][j] = _matrix[i][j] - m[i][j];
						}
					}
					return result;
				}

				else throw invalid_argument("Матрицы разных размеров!");
			}
			catch (invalid_argument err) {
				cerr << err.what();
			}
		}

		matrix<T> operator/(matrix<T> m) {

			try {
				if (_row == m._row && _col == m._col) {
					matrix<T> result(_row, _col);
					for (int i = 0; i < _row; i++) {
						for (int j = 0; j < _col; j++) {
							result[i][j] = (m[i][j] == 0 ? 0 : _matrix[i][j] / m[i][j]);
						}
					}
					return result;
				}

				else throw invalid_argument("Матрицы разных размеров!");
			}
			catch (invalid_argument err) {
				cerr << err.what();
			}
		}

		matrix<T> operator*(matrix<T> m) {

			try {
				if (_row == m._row && _col == m._col) {
					matrix<T> result(_row, _col);
					for (int i = 0; i < _row; i++) {
						for (int j = 0; j < _col; j++) {
							result[i][j] = _matrix[i][j] * m[i][j];
						}
					}
					return result;
				}

				else throw invalid_argument("Матрицы разных размеров!");
			}
			catch (invalid_argument err) {
				cerr << err.what();
			}
		}
		template <typename type>
		friend bool operator==(const matrix<type> left,const matrix<type>& right);
		template <typename type>
		friend bool operator!=(const matrix<type> left, const matrix<type>& right);
	};

	template <typename T>
	ostream& operator<<(ostream& os, const matrix<T> m)
	{
		int maxElemLength = 1;
		for (int i = 0; i < m._row; i++) {
			for (int j = 0; j < m._col; j++) {
				int currElem = int(m[i][j]);

				string currElemString;
				if (currElem == m[i][j]) {
					currElemString = to_string(currElem);
				}
				else currElemString = to_string(m[i][j]);

				if (currElemString.size() > maxElemLength) maxElemLength = currElemString.size();
			}
		}

		for (int i = 0; i < m._row; i++) {
			for (int j = 0; j < m._col; j++) {

				cout << setw(maxElemLength) << m[i][j] << " ";
				//for (int k = 0; k < maxElemLength - to_string(m[i][j]).size(); k++) cout << " ";
			}
			cout << endl;
		}
		return os;
	}
	template <typename T>
	istream& operator>>(istream& is, matrix<T>& m)
	{
		if (m._row != 0 && m._col != 0) cout << "Введите по " << m._col << " элементов в каждую строку\n";
		for (int i = 0; i < m._row; i++) {
			cout << i + 1 << ". ";
			for (int j = 0; j < m._col; j++) {
				is >> m[i][j];
			}
		}
		return is;
	}

	template<typename type>
	bool operator==(const matrix<type> left, const matrix<type>& right)
	{
		try {
			if (left._row == right._row && left._col == right._col) {

				for (int i = 0; i < left._row; i++) {
					for (int j = 0; j < left._col; j++) {
						if (left[i][j] != right[i][j]) return false;
					}
					return true;
				}
			}
			else throw invalid_argument("Матрицы разных размеров!");
		}
		catch (invalid_argument err) {

			cerr << err.what();
		}
	}

	template<typename type>
	bool operator!=(const matrix<type> left, const matrix<type>& right)
	{
		return !(left==right);
	}

	

	
}

