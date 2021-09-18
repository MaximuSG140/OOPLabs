#include<utility>
#include "RNA.h"

RNA::RNANucleotideReference& RNA::RNANucleotideReference::operator=(const nucleotide value)
{
	if(index >= 4 * This->storage.Size())
	{
		This->buffer[index % 4] = value;
		return *this;
	}
	NucleotideBuffer temporaryBuffer(This->storage[index / 4]);
	temporaryBuffer[index % 4] = value;
	This->storage[index / 4] = temporaryBuffer.GetStake();
	return *this;
}

RNA::RNANucleotideReference& RNA::RNANucleotideReference::operator=(const RNANucleotideReference& other)
{
	return (*this) = static_cast<nucleotide>((*other.This)[other.index]);
}

RNA::RNANucleotideReference::operator const nucleotide() const
{
	if(index >= 4 * This->storage.Size())
	{
		return This->buffer[index % 4];
	}
	return NucleotideBuffer((This->storage)[index / 4])[index % 4];
}

RNA::RNA() = default;

RNA::RNA(const vector<nucleotide>&chain)
{
	for (unsigned int i = 0; i < chain.Size(); ++i)
	{
		AddNucleotide(static_cast<vector<nucleotide>>(chain)[i]);
	}
}

RNA::RNA(const vector<nucleotide>&& chain)
{
	for (unsigned int i = 0; i < chain.Size(); ++i)
	{
		AddNucleotide(static_cast<vector<nucleotide>>(chain)[i]);
	}
}

RNA::RNA(const int capacity)
{
	storage = vector<NucleotideStake>(capacity/4, static_cast<nucleotide>(0));
	buffer = NucleotideBuffer(capacity%4, static_cast<nucleotide>(0));
}

RNA::RNA(const int capacity, const nucleotide baseValue)
{
	storage = vector<NucleotideStake>(capacity / 4, NucleotideBuffer(4, baseValue).GetStake());
	buffer = NucleotideBuffer(capacity % 4, baseValue);
}

RNA::RNA(const RNA& r) = default;

RNA::RNA(const RNA&& r)
{
	storage = r.storage;
	buffer = r.buffer;
}

RNA::~RNA() = default;

unsigned int RNA::GetSize()const
{
	return storage.Size() * 4 + buffer.GetAmmount();
}

unsigned RNA::GetLength()const
{
	return  GetSize();
}

unsigned RNA::GetCapacity()const
{
	return storage.Size();
}

unsigned int RNA::GetCardinality(const nucleotide example)const
{
	unsigned int exampleEncounters = 0;
	for(unsigned int i = 0; i < GetSize(); ++i)
	{
		if(example == static_cast<RNA>(*this)[i])
		{
			exampleEncounters++;
		}
	}
	return exampleEncounters;
}

std::unordered_map<nucleotide, int, std::hash<int>> RNA::GetCardinality() const
{
	std::unordered_map<nucleotide, int, std::hash<int>> resultMap{{adenine, 0}, {thymine, 0}, {guanine, 0}, {thymine, 0}};
	for(unsigned int i = 0; i < GetSize(); ++i)
	{
		resultMap[static_cast<RNA>(*this)[i]]++;
	}
	return resultMap;
}

void RNA::AddNucleotide(const nucleotide n)
{
	PushBuffer();
	buffer.AddNucleotide(n);
	PushBuffer();
}

RNA RNA::Trim(const unsigned int lastIndex)
{
	if(lastIndex >= GetSize())
	{
		throw invalid_index_exception(lastIndex, 0, GetSize() - 1);
	}
	vector<NucleotideStake> newStorage(lastIndex / 4);
	for(unsigned int i = 0; i < lastIndex / 4; ++i)
	{
		newStorage[i] = storage[i];
	}
	NucleotideBuffer newBuffer;
	for(unsigned int i = lastIndex - lastIndex % 4; i <= lastIndex; ++i)
	{
		newBuffer.AddNucleotide((*this)[i]);
	}
	this->buffer = newBuffer;
	this->storage = newStorage;
	PushBuffer();
	return *this;
}

void RNA::PushBuffer()
{
	if(buffer.IsFull())
	{
		storage.push_back(buffer.GetStake());
		buffer.Clear();
	}
}

RNA RNA::operator+(const RNA& r) const
{
	RNA res;
	for (unsigned int i = 0; i < GetSize(); ++i)
	{
		res.AddNucleotide(static_cast<RNA>(*this)[i]);
	}
	for(unsigned int i = 0; i < r.GetSize(); ++i)
	{
		res.AddNucleotide(static_cast<RNA>(r)[i]);
	}
	return res;
}

RNA& RNA::operator=(const RNA& r)= default;

RNA& RNA::operator=(RNA&& r) = default;

RNA RNA::operator!() const
{
	RNA res;
	for(unsigned int i = 0; i < storage.Size() * 4; ++i)
	{
		res.AddNucleotide(GetComplimentaryNucleotide(static_cast<RNA>(*this)[i]));
	}
	res.PushBuffer();
	res.buffer = !(this->buffer);
	return res;
}

bool RNA::operator==(const RNA& r)const
{
	return storage == r.storage && buffer == r.buffer;
}

bool RNA::operator!=(const RNA& r) const
{
	return !(*this == r);
}


bool RNA::IsComplimentary(const RNA& r)const
{
	if(storage.Size() != r.storage.Size())
	{
		return false;
	}
	for(unsigned int i = 0; i < storage.Size(); ++i)
	{
		if(!NucleotideBuffer(static_cast<vector<char>>(storage)[i]).IsComplimentary(static_cast<vector<char>>(r.storage)[i]))
		{
			return false;
		}
	}
	return buffer.IsComplimentary(r.buffer);
}

RNA::RNANucleotideReference RNA::operator[](const unsigned int index)
{
	if(index >= GetSize() || index < 0)
	{
		throw invalid_index_exception(index, 0, GetSize() - 1);
	}
	return RNANucleotideReference(this, index);
}

/**
 * \brief
 *  Splits RNA into two
 * \param index
 *	Index of last element of first RNA after splitting
 * \return
 *	Pair of RNA first is before given index, second - after
 */
std::pair<RNA, RNA> RNA::Split(const unsigned int index) const
{
	if (index >= GetSize() || index < 0)
	{
		throw invalid_index_exception(index, 0, GetSize() - 1);
	}
	RNA firstPart, secondPart;
	for(unsigned int i = 0; i <= index; ++i)
	{
		firstPart.AddNucleotide(static_cast<RNA>(*this)[i]);
	}
	for(unsigned int i = index + 1; i < GetSize(); ++i)
	{
		secondPart.AddNucleotide(static_cast<RNA>(*this)[i]);
	}
	return std::make_pair(firstPart, secondPart);
}

