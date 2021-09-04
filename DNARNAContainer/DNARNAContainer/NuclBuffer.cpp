#include "NuclBuffer.h"

void NuclBuffer::AddNucl(Nucleotide newNucl)
{
	current &= (1 << (nuclAmmount << 1) - 1) << ((4 - nuclAmmount) << 1);
	current += newNucl << ((3 - nuclAmmount) << 1);
}
