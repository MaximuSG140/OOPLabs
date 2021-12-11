#pragma once
#include <exception>
#include <string>

class UnknownRuleSequence final :
	public std::exception
{
public:
	explicit UnknownRuleSequence(size_t error_line, size_t error_element, std::string unknown_word);
	[[nodiscard]] char const* what() const override;
	
private:
	std::string error_message_;
	size_t error_line_;
	size_t error_element_;
	std::string unknown_word_;
};

