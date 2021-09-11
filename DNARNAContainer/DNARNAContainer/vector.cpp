#pragma once
#include "vector.h"

template <class T>
vector<T>::vector() = default;

template <class T>
vector<T>::vector(const unsigned int n) :size(n), capacity(n)
{
	storage = new T[n];
}

template <class T>
vector<T>::vector(const unsigned int n, const T example):vector(n)
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
		return *this;
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
	return *this;
}

template <class T>
void vector<T>::push_back(const T value)
{
	if(size == capacity)
	{
		if(size == 0)
		{
			storage = new T[1];
			capacity = 1;
		}
		else
		{
			T* oldStorage = storage;
			storage = new T[capacity *= 2];
			for(int i = 0; i < size; ++i)
			{
				storage[i] = oldStorage[i];
			}
			delete[] oldStorage;
		}
	}
	storage[size] = value;
	size++;
}

template <class T>
unsigned int vector<T>::Size() const
{
	return size;
}

template <class T>
T& vector<T>::operator[](unsigned int index)
{
	return storage[index];
}

template <class T>
bool vector<T>::operator==(const vector& otherVector) const
{
	if(size != otherVector.size || capacity != otherVector.capacity)
	{
		return false;
	}
	for(int i = 0; i < size; ++i)
	{
		if(storage[i] != otherVector[i])
		{
			return false;
		}
	}
	return true;
}


