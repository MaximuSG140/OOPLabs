#pragma once
#include<initializer_list>
#include "RNAExceptions.h"

template <class T> class vector
{
public:
	vector();
	explicit vector(unsigned int n);
	explicit vector(unsigned int n, T example);
	vector(const std::initializer_list<T>& initList);
	vector(const vector<T>& example);
	vector(const vector<T>&& example);

	~vector();

	vector<T>& operator=(const vector<T>& example);

	void push_back(T value);
	unsigned int Size() const;
	T& operator[](unsigned int index);
	bool operator==(const vector& otherVector) const;
private:
	T* storage = nullptr;
	unsigned int size = 0;
	unsigned int capacity = 0;
};

template <class T>
vector<T>::vector() = default;

template <class T>
vector<T>::vector(const unsigned int n) :size(n), capacity(n)
{
	storage = new T[n];
}

template <class T>
vector<T>::vector(const unsigned int n, const T example) :vector(n)
{
	for (unsigned int i = 0; i < n; ++i)
	{
		storage[i] = example;
	}
}

template <class T>
vector<T>::vector(const std::initializer_list<T>& initList) :vector(initList.size())
{
	for (unsigned int i = 0; i < size; ++i)
	{
		storage[i] = initList.begin()[i];
	}
}

template <class T>
vector<T>::vector(const vector<T>& example) :vector(example.size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		storage[i] = example.storage[i];
	}
}

template <class T>
vector<T>::vector(const vector<T>&& example) :vector(example.size)
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
	if (this == &example)
	{
		return *this;
	}
	const T* oldStorage = storage;
	storage = new T[example.capacity];
	for (unsigned int i = 0; i < example.size; ++i)
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
	if (size == capacity)
	{
		if (size == 0)
		{
			storage = new T[1];
			capacity = 1;
		}
		else
		{
			T* oldStorage = storage;
			storage = new T[capacity *= 2];
			for (unsigned int i = 0; i < size; ++i)
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
	if (index < 0 || index >= size)
	{
		throw invalid_index_exception(index, 0, size - 1);
	}
	return storage[index];
}

template <class T>
bool vector<T>::operator==(const vector& otherVector) const
{
	if (size != otherVector.size)
	{
		return false;
	}
	for (unsigned int i = 0; i < size; ++i)
	{
		if (storage[i] != otherVector.storage[i])
		{
			return false;
		}
	}
	return true;
}

