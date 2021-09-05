#pragma once
#include"Nucleotides.h"

class NucleotideBuffer
{
public:
	void AddNucleotide(nucleotide newNucleotide);
	void RemoveLast();
	void Clear();
	NucleotideStake GetStake() const;
	nucleotide operator[](unsigned int index) const;
	NucleotideBuffer();
	NucleotideBuffer(int number, nucleotide value);
	NucleotideBuffer(NucleotideStake basis);
	bool IsComplimentary(const NucleotideBuffer buffer) const;
	bool IsFull()const;
	NucleotideBuffer& operator! ()const;
private:
	NucleotideStake current = 0;
	int nucleotideAmmount = 0;
};

