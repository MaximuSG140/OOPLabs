#pragma once
#include <exception>

class BadLineFormat final :
	public std::exception
{
public:
	explicit BadLineFormat(size_t unread_elements);
	size_t GetElemFromEnd()const;
private:
	size_t unread_elements_;
};

