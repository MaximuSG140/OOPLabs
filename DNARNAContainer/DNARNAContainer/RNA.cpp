#include<utility>
#include "RNA.h"

RNA::RNA() = default;

RNA::RNA(const vector<nucleotide>&chain)
{
	for (int i = 0; i < chain.Size(); ++i)
	{
		AddNucleotide(static_cast<vector<nucleotide>>(chain)[i]);
	}
}

RNA::RNA(const int capacity)
{
	storage = vector<NucleotideStake>(capacity/4);
	buffer = NucleotideBuffer(capacity%4, static_cast<nucleotide>(0));
}

RNA::RNA(const int capacity, const nucleotide baseValue)
{
	storage = vector<NucleotideStake>(capacity / 4, NucleotideBuffer(4, baseValue).GetStake());
	buffer = NucleotideBuffer(capacity % 4, baseValue);
}

RNA::RNA(const RNA& r) = default;

RNA::~RNA() = default;

unsigned int RNA::GetCapacity()const
{
	return storage.Size() * 4 + buffer.GetAmmount();
}

unsigned int RNA::GetCardinality(const nucleotide example) const
{
	unsigned int exampleEncounters = 0;
	for(unsigned int i = 0; i < GetCapacity(); ++i)
	{
		if(example == (*this)[i])
		{
			exampleEncounters++;
		}
	}
	return exampleEncounters;
}

std::unordered_map<nucleotide, int, std::hash<int>> RNA::GetCardinality() const
{
	std::unordered_map<nucleotide, int, std::hash<int>> resultMap{{adenine, 0}, {thymine, 0}, {guanine, 0}, {thymine, 0}};
	for(unsigned int i = 0; i < GetCapacity(); ++i)
	{
		resultMap[(*this)[i]]++;
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
	for (unsigned int i = 0; i < GetCapacity(); ++i)
	{
		res.AddNucleotide((*this)[i]);
	}
	for(unsigned int i = 0; i < r.GetCapacity(); ++i)
	{
		res.AddNucleotide(r[i]);
	}
	return res;
}

RNA& RNA::operator=(const RNA& r)
{
	this->storage = vector<NucleotideStake>(r.storage);
	this->buffer = r.buffer;
	return *this;
}

RNA& RNA::operator=(RNA&& r) = default;

RNA RNA::operator!() const
{
	RNA res;
	for(unsigned int i = 0; i < storage.Size() * 4; ++i)
	{
		res.AddNucleotide(GetComplimentaryNucleotide((*this)[i]));
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

nucleotide RNA::operator[](const unsigned int index) const
{
	if(index >= GetCapacity() || index < 0)
	{
		throw std::out_of_range("index is out of range of allowed values");
	}
	if(index >= 4 * storage.Size())
	{
		return buffer[index % 4];
	}
	return NucleotideBuffer(static_cast<vector<NucleotideStake>>(storage)[index / 4])[index % 4];
}

/**
 * \brief
 *  Splits RNA into two
 * \param index
 *	Index of last element of first RNA after splitting
 * \return
 *	Pair of RNA first is before given index, second - after
 */
std::pair<RNA, RNA> RNA::Split(const int index) const
{
	RNA firstPart, secondPart;
	for(int i = 0; i <= index; ++i)
	{
		firstPart.AddNucleotide((*this)[i]);
	}
	for(unsigned int i = index + 1; i < GetCapacity(); ++i)
	{
		secondPart.AddNucleotide((*this)[i]);
	}
	
	return std::make_pair(firstPart, secondPart);
}

