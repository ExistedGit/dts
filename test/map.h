#pragma once
#include "dts.h"

namespace dts {
	template <typename K, typename V>
	class Pair {
	public:
		K key;
		V value;

		Pair(const K& _key, const V& _value) {
			key = _key;
			value = _value;
		}
	};

	template <typename T, typename V>
	class Map {
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
		Map();
		Map(const initializer_list<Pair<T, V>>& il);
		~Map();

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

		V& operator[](const T& key) {
			return find(key);
		}


	};
};

namespace dts {
	template<typename T, typename V>
	inline Map<T, V>::Node::Node() {
		left = nullptr;
		right = nullptr;
	}
	template<typename T, typename V>
	inline Map<T, V>::Node::Node(const T& _key, const V& _value, Node* _left, Node* _right) {
		left = _left;
		right = _right;
		key = _key;
		value = _value;
	}
	template<typename T, typename V>
	inline void Map<T, V>::addElemR(const T& key, const V& value, Node* node) {
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
	inline int Map<T, V>::getHeightR(Node* node) {
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
	inline void Map<T, V>::Balance(Node*& node, const T& key) {
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
	inline void Map<T, V>::BalanceR(Node*& node, const T& elem) {
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
	inline bool Map<T, V>::countR(const T& key, Node* node) {
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
	inline void Map<T, V>::inOrderPrint(Node* node) {
		if (node == nullptr) return;

		inOrderPrint(node->left);
		cout << node->value << " ";
		inOrderPrint(node->right);
	}
	template<typename T, typename V>
	inline void Map<T, V>::rightRotate(Node*& node) {
		if (node == nullptr) return;
		Node* nodeCopy = new Node(node->value, node->key, node->left, node->right);
		Node* tmp = nodeCopy->left;
		nodeCopy->left = tmp->right;
		tmp->right = nodeCopy;

		*node = *tmp;
		delete tmp;
	}
	template<typename T, typename V>
	inline void Map<T, V >::leftRotate(Node*& node) {
		if (node == nullptr) return;

		Node* nodeCopy = new Node(node->value, node->key, node->left, node->right);

		Node* tmp = nodeCopy->right;
		nodeCopy->right = tmp->left;
		tmp->left = nodeCopy;
		*node = *tmp;
		delete tmp;
	}
	template<typename T, typename V>
	inline void Map<T, V>::bigRightRotate(Node*& node) {
		rightRotate(node->right);

		leftRotate(node);
	}
	template<typename T, typename V>
	inline void Map<T, V>::bigLeftRotate(Node*& node) {
		leftRotate(node->left);
		rightRotate(node);
	}
	template<typename T, typename V>
	inline void Map<T, V>::printR(const std::string& prefix, const Node* node, bool isLeft, bool rightExists)
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
	inline V& Map<T, V>::findR(const T& key, Node* node) {
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
	inline Map<T, V>::Map() {
		_root = nullptr;
		lastFound = nullptr;
	}
	template<typename T, typename V>
	inline Map<T, V>::Map(const initializer_list<Pair<T, V>>& il) : Map() {
		for (int i = 0; i < il.size(); i++) {
			Pair<T, V> pair = *(il.begin() + i);
			push(pair.key, pair.value);
		}
	}
	template<typename T, typename V>
	inline Map<T, V>::~Map() {
		clear();
	}
	template<typename T, typename V>
	inline void Map<T, V>::clearR(Node*& node) {
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
	inline void Map<T, V>::clear() {
		clearR(_root);


	}
	template<typename T, typename V>
	inline void Map<T, V>::push(const T& key, const V& value) {
		addElemR(key, value);
	}
	template<typename T, typename V>
	inline int Map<T, V>::getHeight() {
		return getHeightR(_root) - 1;
	}
	template<typename T, typename V>
	inline bool Map<T, V>::removeR(Node*& node, const T& key) {
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
	inline bool Map<T, V>::count(const T& key) {
		return countR(key, _root);
	}

	template<typename T, typename V>
	inline bool Map<T, V>::remove(const T& key) {
		bool result = removeR(_root, key);
		return result;
	}

	// In Order
	template<typename T, typename V>
	inline void Map<T, V>::printIO() {
		inOrderPrint(_root);
	}
	template<typename T, typename V>
	inline void Map<T, V>::print()
	{
		//system("cls");
		printR("", _root, false);
		//system("pause");
	}

	template<typename T, typename V>
	inline V& Map<T, V>::find(const T& key) {

		if (lastFound != nullptr) {
			if (lastFound->key == key) return lastFound->key;
		}
		return findR(key, _root);
	}
};