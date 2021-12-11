#include "UnknownRuleSequence.h"

UnknownRuleSequence::UnknownRuleSequence(const size_t error_line,
	const size_t error_element,
	std::string unknown_word) :
error_line_(error_line),
error_element_(error_element),
unknown_word_(std::move(unknown_word))
{
	error_message_ = "Error, unknown rule sequence: " + unknown_word_ + "\n";
	error_message_ += "Line: " + std::to_string(error_line_) + " Element: " + std::to_string(error_element_) + "\n";
}

char const* UnknownRuleSequence::what() const
{
	return error_message_.c_str();
}
