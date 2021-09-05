#include "RNA.h"

RNA::RNA() = default;

RNA::RNA(const int capacity)
{
	storage = std::vector<NucleotideStake>(capacity/4);
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

