#include "BadLineFormat.h"

BadLineFormat::BadLineFormat(const size_t unread_elements) :
	unread_elements_(unread_elements)
{}

size_t BadLineFormat::GetElemFromEnd() const
{
	return unread_elements_;
}
