#include "NucleotideBuffer.h"

NucleotideBuffer::NucleotideReference& NucleotideBuffer::NucleotideReference::operator=(const nucleotide newValue)
{
	This->stake &= ((1 << 8) - 1) - (3 << (6 - 2 * index));
	This->stake |= static_cast<NucleotideStake>(newValue << (6 - 2 * index));
	return *this;
}

NucleotideBuffer::NucleotideReference::operator const nucleotide() const
{
	return static_cast<nucleotide>((This->stake >> (3 - index) * 2) & 3);
}

void NucleotideBuffer::AddNucleotide(const nucleotide newNucleotide)
{
	stake &= NucleotideStake(((1 << nucleotideAmmount * 2) - 1) << (4 - nucleotideAmmount) * 2);
	stake |= newNucleotide << ((3 - nucleotideAmmount) << 1);
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
	stake = 0;
	nucleotideAmmount = 0;
}

NucleotideStake NucleotideBuffer::GetStake() const
{
	return stake;
}

NucleotideBuffer::NucleotideBuffer() = default;

NucleotideBuffer::NucleotideBuffer(const int number, const nucleotide value)
{
	if(number > 4 || number <= 0)
	{
		return;
	}
	for (int i = 0; i < number; i++) 
	{
		this->AddNucleotide(value);
	}
}

NucleotideBuffer::NucleotideBuffer(const NucleotideStake basis)
{
	stake = basis;
	nucleotideAmmount = 4;
}

bool NucleotideBuffer::IsComplimentary(NucleotideBuffer secondNucleotideBuffer) const
{
	if(nucleotideAmmount != secondNucleotideBuffer.nucleotideAmmount)
	{
		return false;
	}
	for(unsigned int i = 0; i < nucleotideAmmount; ++i)
	{
		if(GetComplimentaryNucleotide(static_cast<NucleotideBuffer>(*this)[i]) != secondNucleotideBuffer[i])
		{
			return false;
		}
	}
	return true;
}

bool NucleotideBuffer::IsFull() const
{
	return nucleotideAmmount == 4;
}

unsigned int NucleotideBuffer::GetAmmount() const
{
	return nucleotideAmmount;
}

NucleotideBuffer NucleotideBuffer::operator!()const
{
	NucleotideBuffer res;
	for(unsigned int i = 0; i < nucleotideAmmount; ++i)
	{
		res.AddNucleotide(GetComplimentaryNucleotide(static_cast<NucleotideBuffer>(*this)[i]));
	}
	return res;
}

NucleotideBuffer::NucleotideReference NucleotideBuffer::operator[](const unsigned int index)
{
	return NucleotideReference(this, index);
}

bool NucleotideBuffer::operator==(const NucleotideBuffer& buffer) const
{
	return nucleotideAmmount == buffer.nucleotideAmmount && stake == buffer.stake;
}
