#include "RNA.h"

RNA::RNA() = default;

RNA::RNA(const int capacity)
{
	storage = std::vector<NucleotideStake>(capacity/4);
	buffer.AddNucleotide(a);
}

RNA::RNA(const int capacity, const nucleotide baseValue)
{
	storage = std::vector<NucleotideStake>(capacity / 4, NucleotideBuffer(4, baseValue).GetStake());
	buffer = NucleotideBuffer(capacity % 4, baseValue);
}

RNA::~RNA() = default;

RNA& RNA::operator=(const RNA& r)
{
	this->storage = std::vector<NucleotideStake>(r.storage);
	this->buffer = r.buffer;
	return *this;
}

nucleotide RNA::operator[](const unsigned int index) const
{
	if(index >= 4 * storage.size())
	{
		return buffer[index % 4];
	}
	return NucleotideBuffer(storage[index / 4])[index % 4];
}

