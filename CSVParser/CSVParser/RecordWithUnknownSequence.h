#pragma once
#include <exception>
#include <string>

class RecordWithUnknownSequence final :
	public std::exception
{
public:
	explicit RecordWithUnknownSequence(size_t unread_elements, std::string unknown_word);
	size_t GetElemFromEnd()const;
	std::string GetWord()const;
private:
	size_t unread_elements_;
	std::string unknown_word_;
};

