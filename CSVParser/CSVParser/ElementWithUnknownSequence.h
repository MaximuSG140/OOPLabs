#pragma once
#include <exception>
#include <string>

class ElementWithUnknownSequence final :
	public std::exception
{
public:
	explicit ElementWithUnknownSequence(std::string unknown_word);
	std::string GetWord()const;
private:
	std::string unknown_word_;
};

