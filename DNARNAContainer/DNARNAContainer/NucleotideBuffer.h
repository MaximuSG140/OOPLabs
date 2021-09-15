#pragma once
#include"Nucleotides.h"

class NucleotideBuffer
{
public:
	struct Proxy
	{
		NucleotideBuffer *const This;
		unsigned int index;
		Proxy(NucleotideBuffer *const This, const unsigned int index) : This(This), index(index){}
		Proxy& operator=(const nucleotide newValue);
		operator const nucleotide()const;
	};
	void AddNucleotide(const nucleotide newNucleotide);
	void RemoveLast();
	void Clear();
	NucleotideStake GetStake() const;
	Proxy operator[](unsigned int index);
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

