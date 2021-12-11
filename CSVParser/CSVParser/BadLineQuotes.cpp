#include "BadLineQuotes.h"

BadLineQuotes::BadLineQuotes(const size_t reversed_element_number) :
	reversed_element_number_(reversed_element_number)
{}

size_t BadLineQuotes::GetElemFromEnd() const
{
	return reversed_element_number_;
}
