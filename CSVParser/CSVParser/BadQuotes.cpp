#include "BadQuotes.h"

BadQuotes::BadQuotes(const size_t line_number, const size_t element_number) :
	error_message_("Error, one of screening symbols does not have pair.\n"),
	line_number_(line_number),
	element_number_(element_number)
{
	error_message_ += "Line: ";
	error_message_ += std::to_string(line_number_);
	error_message_ += " Element: ";
	error_message_ += std::to_string(element_number_);
}

char const* BadQuotes::what() const
{
	return error_message_.c_str();
}
