#pragma once
#include<initializer_list>

template <class T> class vector
{
public:
	vector();
	explicit vector(const unsigned int n);
	explicit vector(const unsigned int n, const T example);
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
