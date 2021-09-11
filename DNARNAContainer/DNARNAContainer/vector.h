#pragma once
#include "Nucleotides.h"
template <class T> class vector
{
public:
	vector();
	explicit vector(const int n);
	explicit vector(const int n, const T example);
	vector(const T array[]);
	vector(const vector<T>& example);

	~vector();

	vector<T>& operator=(const vector<T>& example);
private:
	T* storage = nullptr;
	int size = 0;
};


