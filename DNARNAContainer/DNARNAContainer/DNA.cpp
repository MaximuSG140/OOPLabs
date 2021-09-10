#include "DNA.h"

DNA::DNA(const RNA& f, const RNA& s):firstChain(f), secondChain(s)
{
	if(!f.IsComplimentary(s))
	{
		firstChain = secondChain = RNA();
	}
}
