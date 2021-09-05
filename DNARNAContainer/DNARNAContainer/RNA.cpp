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

RNA::RNA(RNA& r) = default;

RNA::~RNA() = default;

void RNA::AddNucleotide(const nucleotide n)
{
	if(buffer.IsFull())
	{
		storage.push_back(buffer.GetStake());
		buffer.Clear();
	}
	buffer.AddNucleotide(n);
}

void RNA::PushBuffer()
{
	if(!buffer.IsFull())
	{
		storage.push_back(buffer.GetStake());
		buffer.Clear();
	}
}

RNA& RNA::operator+(RNA r)
{
	RNA* res = new RNA(*this);
	for(int i = 0; i < r.storage.size() * 4; ++i)
	{
		res->AddNucleotide(r[i]);
	}

}

RNA& RNA::operator=(const RNA& r)
{
	this->storage = std::vector<NucleotideStake>(r.storage);
	this->buffer = r.buffer;
	return *this;
}

RNA& RNA::operator!() const
{
	RNA* res = new RNA();				//where to delete?
	for(unsigned int i = 0; i < storage.size() * 4; ++i)
	{
		res->AddNucleotide((*this)[i]);
	}
	res->PushBuffer();
	res->buffer = !(this->buffer);
	return *res;
}

bool RNA::IsComplimentary(const RNA r)
{
	if(storage.size() != r.storage.size())
	{
		return false;
	}
	for(unsigned int i = 0; i < storage.size(); ++i)
	{
		if(!NucleotideBuffer(storage[i]).IsComplimentary(r.storage[i]))
		{
			return false;
		}
	}
	return buffer.IsComplimentary(r.buffer);
}

nucleotide RNA::operator[](const unsigned int index) const
{
	if(index >= 4 * storage.size())
	{
		return buffer[index % 4];
	}
	return NucleotideBuffer(storage[index / 4])[index % 4];
}

