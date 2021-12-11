#pragma once
#include <exception>

class BadLineQuotes final :
	public std::exception
{
public:
	explicit BadLineQuotes(size_t reversed_element_number);
	size_t GetElemFromEnd()const;
private:
	size_t reversed_element_number_;
};

