#include "NucleotideBuffer.h"

void NucleotideBuffer::AddNucleotide(const nucleotide newNucleotide)
{
	current &= NucleotideStake((1 << (nucleotideAmmount << 1) - 1) << ((4 - nucleotideAmmount) << 1));
	current += newNucleotide << ((3 - nucleotideAmmount) << 1);
}

void NucleotideBuffer::RemoveLast()
{
	if (nucleotideAmmount == 0)
	{
		return;
	}
	nucleotideAmmount--;
}

void NucleotideBuffer::Clear()
{
	current = 0;
	nucleotideAmmount = 0;
}

NucleotideStake NucleotideBuffer::GetStake() const
{
	return current;
}

NucleotideBuffer::NucleotideBuffer() = default;

NucleotideBuffer::NucleotideBuffer(int number, nucleotide value)
{
	for (int i = 0; i < number; i++) 
	{
		this->AddNucleotide(value);
	}
}
