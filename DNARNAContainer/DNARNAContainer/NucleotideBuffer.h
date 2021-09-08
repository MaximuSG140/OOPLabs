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
	bool operator==(const NucleotideBuffer& buffer) const;
	NucleotideBuffer();
	NucleotideBuffer(int number, nucleotide value);
	NucleotideBuffer(NucleotideStake basis);
	bool IsComplimentary(const NucleotideBuffer secondNucleotideBuffer) const;
	bool IsFull()const;
	unsigned int GetAmmount()const;
	NucleotideBuffer operator! ()const;
private:
	NucleotideStake current = 0;
	unsigned int nucleotideAmmount = 0;
};

