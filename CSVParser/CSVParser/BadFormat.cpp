#include "BadFormat.h"
#include <string>

BadFormat::BadFormat(const size_t line_number, const size_t element_number) :
	line_number_(line_number),
	element_number_(element_number)
{
	msg_ += "Wrong csv format, ";
	msg_ += "line: ";
	msg_ += std::to_string(line_number_);
	msg_ += ", element: ";
	msg_ += std::to_string(element_number_);
	msg_ += ".";
}

char const* BadFormat::what() const
{
	return msg_.c_str();
}
