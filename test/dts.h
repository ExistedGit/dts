#pragma once
#ifndef DTS_INCLUDED
#define DTS_INCLUDED
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <mutex> // для инициализации вектора списком
using namespace std;

namespace dts {
	
	template<typename T>
	class linked_list;
	template<typename T>
	class List;
	template<typename T>
	class Deque;
	template<typename T>
	class Stack;
	template<typename T>
	class Queue;

	template <typename K, typename V>
	class Pair;
	template<typename T, typename V>
	class Map;


	template<typename Type>
	class Vector;

	class String;
	class StringBuilder;

	inline int strLen(const char* s) {
		int size = 0;
		for (int i = 0; s[i] != '\0'; i++) {
			size++;
		}
		return size;
	}

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
	
	
	

	
}
#endif