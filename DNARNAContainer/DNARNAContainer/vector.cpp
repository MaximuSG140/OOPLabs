#pragma once
#include "vector.h"

template <class T>
vector<T>::vector() = default;

template <class T>
vector<T>::vector(const int n)
{
	storage = new T[n];
	size = n;
}

template <class T>
vector<T>::vector(const int n, const T example)
{
	storage = new T[n];
	size = n;
	for(int i = 0; i < n; ++i)
	{
		storage[i] = example;
	}
}

template <class T>
vector<T>::vector(const T array[]):vector(sizeof(array)/sizeof(T))
{
	for(int i = 0; i < size; ++i)
	{
		storage[i] = array[i];
	}
}

template <class T>
vector<T>::vector(const vector<T>& example) :vector(example.storage){}

template <class T>
vector<T>::~vector()
{
	delete[] storage;
}

template <class T>
vector<T>& vector<T>::operator=(const vector<T>& example)
{
	delete[] storage;
	storage = new T[example.size];
	size = example.size;
	for(int i = 0; i < size; ++i)
	{
		storage[i] = example.storage[i];
	}
}

