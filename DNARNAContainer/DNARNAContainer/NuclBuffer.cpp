#include "NuclBuffer.h"

void NuclBuffer::AddNucl(Nucleotide newNucl)
{
	current &= (1 << (nuclAmmount << 1) - 1) << ((4 - nuclAmmount) << 1);
	current += newNucl << ((3 - nuclAmmount) << 1);
}

void NuclBuffer::RemoveLast()
{
	if (nuclAmmount == 0)
	{
		return;
	}
	nuclAmmount--;
}

void NuclBuffer::Clear()
{
	current = 0;
	nuclAmmount = 0;
}

NuclStake NuclBuffer::GetStake()
{
	return current;
}

NuclBuffer::NuclBuffer() {}

NuclBuffer::NuclBuffer(int number, Nucleotide value)
{
	for (int i = 0; i < number; i++) 
	{
		this->AddNucl(value);
	}
}
