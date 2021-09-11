#pragma once
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

	void push_back(T value);
private:
	T* storage = nullptr;
	int size = 0;
	int capacity = 0;
};


