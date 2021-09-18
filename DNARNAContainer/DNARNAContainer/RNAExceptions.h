#pragma once
#include <exception>

class invalid_index_exception : std::exception
{
private:
	unsigned int index;
	unsigned int maximumIndex;
	unsigned int minimumIndex;
public:
	char const* what() const override;
	invalid_index_exception(const unsigned int i, const unsigned int min, const unsigned int max) :exception(), index(i), maximumIndex(max), minimumIndex(min) {}
	bool operator==(const invalid_index_exception& e)const;
};

