#pragma once
#include<utility>
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

RNA& RNA::operator+(const RNA& r) const
{
	RNA* res = new RNA();
	for (int i = 0; i < storage.size() * 4 + buffer.GetAmmount(); ++i)
	{
		res->AddNucleotide((*this)[i]);
	}
	for (int i = 0; i < buffer.GetAmmount(); ++i)
	{
		res->AddNucleotide(buffer[i]);
	}
	for(int i = 0; i < r.storage.size() * 4 + r.buffer.GetAmmount(); ++i)
	{
		res->AddNucleotide(r[i]);
	}
	return *res;
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

bool RNA::operator==(const RNA& r)const
{
	return storage == r.storage && buffer == r.buffer;
}

bool RNA::operator!=(const RNA& r) const
{
	return !(*this == r);
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

/**
 * \brief
 *  Splits RNA into two
 * \param index
 *	Index of last element of first RNA after splitting
 * \return
 *	Pair of pointers on RNA first is before given index, second - after
 */
std::pair<RNA*, RNA*> RNA::Split(const int index)
{
	RNA *firstPart, *secondPart;
	firstPart = new RNA();
	secondPart = new RNA();
	for(int i = 0; i < index; ++i)
	{
		firstPart->AddNucleotide((*this)[i]);
	}
	for(int i = index; i < storage.size()*4 + buffer.GetAmmount(); ++i)
	{
		secondPart->AddNucleotide((*this)[i]);
	}
	std::pair<int, int>res = std::make_pair(2, 3);
	
	return std::make_pair(firstPart, secondPart);
}

