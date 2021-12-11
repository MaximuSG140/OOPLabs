#include "ElementWithUnknownSequence.h"

ElementWithUnknownSequence::ElementWithUnknownSequence(std::string unknown_word) :
	unknown_word_(std::move(unknown_word))
{}

std::string ElementWithUnknownSequence::GetWord()const
{
	return unknown_word_;
}
