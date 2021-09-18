#include "DNAExceptions.h"

char const* RNAs_are_not_complimentary::what() const
{
	return "RNA which DNA object should consist are not complimentary";
}
