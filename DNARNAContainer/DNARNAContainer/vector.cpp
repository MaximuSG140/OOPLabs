#pragma once
#include "vector.h"

template <class T>
vector<T>::vector() = default;

template <class T>
vector<T>::vector(const int n) :size(n), capacity(n)
{
	storage = new T[n];
}

template <class T>
vector<T>::vector(const int n, const T example):vector(n)
{
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
	if(this == &example)
	{
		return (*this);
	}
	const T* oldStorage = storage;
	storage = new T[example.capacity];
	for(int i = 0; i < example.size(); ++i)
	{
		storage[i] = example.storage[i];
	}
	delete[] oldStorage;
	size = example.size;
	capacity = example.capacity;
	return (*this);
}

