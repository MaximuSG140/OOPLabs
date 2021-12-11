#include "RecordWithUnknownSequence.h"

RecordWithUnknownSequence::RecordWithUnknownSequence(const size_t unread_elements,
                                                     std::string unknown_word) :
	unread_elements_(unread_elements),
	unknown_word_(std::move(unknown_word))
{}

size_t RecordWithUnknownSequence::GetElemFromEnd() const
{
	return unread_elements_;
}

std::string RecordWithUnknownSequence::GetWord() const
{
	return unknown_word_;
}
