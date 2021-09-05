#include "NucleotideBuffer.h"

void NucleotideBuffer::AddNucleotide(const nucleotide newNucleotide)
{
	current &= NucleotideStake(((1 << nucleotideAmmount * 2) - 1) << (4 - nucleotideAmmount) * 2);
	current |= newNucleotide << ((3 - nucleotideAmmount) << 1);
	nucleotideAmmount++;
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

NucleotideBuffer::NucleotideBuffer(const int number, const nucleotide value)
{
	for (int i = 0; i < number; i++) 
	{
		this->AddNucleotide(value);
	}
}

NucleotideBuffer::NucleotideBuffer(NucleotideStake basis)
{
	current = basis;
	nucleotideAmmount = 4;
}

nucleotide NucleotideBuffer::operator[](unsigned int index) const
{
	return static_cast<nucleotide>((current >> (3 - nucleotideAmmount) * 2) & 3);
}
