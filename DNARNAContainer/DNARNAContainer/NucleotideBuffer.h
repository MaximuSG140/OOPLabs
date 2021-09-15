#pragma once
#include"Nucleotides.h"

class NucleotideBuffer
{
public:
	struct proxy
	{
		NucleotideBuffer *const This;
		unsigned int index;
		proxy(NucleotideBuffer *const This, const unsigned int index) : This(This), index(index){}
		void operator=(const nucleotide newValue)const
		{
			This->current &= ((1 << 8) - 1) - (3 << (6 - 2 * index));
			This->current |= static_cast<int>(newValue) << (6 - 2 * index);
		}
		operator const nucleotide()const;
	};
	void AddNucleotide(const nucleotide newNucleotide);
	void RemoveLast();
	void Clear();
	NucleotideStake GetStake() const;
	proxy operator[](unsigned int index);
	bool operator==(const NucleotideBuffer& buffer) const;
	NucleotideBuffer();
	NucleotideBuffer(const int number, const nucleotide value);
	NucleotideBuffer(const NucleotideStake basis);
	bool IsComplimentary(NucleotideBuffer secondNucleotideBuffer) const;
	bool IsFull()const;
	unsigned int GetAmmount()const;
	NucleotideBuffer operator! ()const;
private:
	NucleotideStake current = 0;
	unsigned int nucleotideAmmount = 0;
};

