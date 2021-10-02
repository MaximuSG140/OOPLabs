#pragma once
#include"Nucleotides.h"

class NucleotideBuffer
{
public:
	class NucleotideReference
	{
	public:
		NucleotideReference(NucleotideBuffer *const This, const unsigned int index) : This(This), index(index){}
		NucleotideReference& operator=(nucleotide newValue);
		operator const nucleotide()const;
	private:
		NucleotideBuffer *const This;
		unsigned int index;
	};
	void AddNucleotide(nucleotide newNucleotide);
	void RemoveLast();
	void Clear();
	NucleotideStake GetStake() const;
	NucleotideReference operator[](unsigned int index);
	bool operator==(const NucleotideBuffer& buffer) const;
	NucleotideBuffer();
	NucleotideBuffer(int number, nucleotide value);
	NucleotideBuffer(NucleotideStake basis);
	bool IsComplimentary(NucleotideBuffer secondNucleotideBuffer) const;
	bool IsFull()const;
	unsigned int GetAmmount()const;
	NucleotideBuffer operator! ()const;
private:
	NucleotideStake stake = 0;
	unsigned int nucleotideAmmount = 0;
};

