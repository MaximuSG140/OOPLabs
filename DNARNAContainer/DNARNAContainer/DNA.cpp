#include "DNA.h"
#include "DNAExceptions.h"

DNA::DNA(const RNA& f, const RNA& s):firstChain(f), secondChain(s)
{
	if(!f.IsComplimentary(s))
	{
		throw RNAs_are_not_complimentary();
	}
}
