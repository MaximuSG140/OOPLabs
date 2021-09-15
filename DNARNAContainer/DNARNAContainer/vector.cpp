#pragma once
#include "vector.h"
#include "Nucleotides.h"

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
	for(unsigned int i = 0; i < n; ++i)
	{
		storage[i] = example;
	}
}

template <class T>
vector<T>::vector(const std::initializer_list<T>& initList):vector(initList.size())
{
	for(unsigned int i = 0; i < size; ++i)
	{
		storage[i] = initList.begin()[i];
	}
}

template <class T>
vector<T>::vector(const vector<T>& example):vector(example.size)
{
	for(unsigned int i = 0; i < size; ++i)
	{
		storage[i] = example.storage[i];
	}
}

template <class T>
vector<T>::vector(const vector<T>&& example):vector(example.size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		storage[i] = example.storage[i];
	}
};

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
	for(unsigned int i = 0; i < example.size; ++i)
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
			for(unsigned int i = 0; i < size; ++i)
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
	if(size != otherVector.size)
	{
		return false;
	}
	for(unsigned int i = 0; i < size; ++i)
	{
		if(storage[i] != otherVector.storage[i])
		{
			return false;
		}
	}
	return true;
}

template vector<nucleotide>;
template vector<NucleotideStake>;
template vector<char>;
