#pragma once
#include"Nucleotides.h"

class NucleotideBuffer
{
public:
	void AddNucleotide(const nucleotide newNucleotide);
	void RemoveLast();
	void Clear();
	NucleotideStake GetStake() const;
	nucleotide operator[](unsigned int index) const;
	bool operator==(const NucleotideBuffer& buffer) const;
	NucleotideBuffer();
	NucleotideBuffer(const int number, const nucleotide value);
	NucleotideBuffer(const NucleotideStake basis);
	bool IsComplimentary(const NucleotideBuffer secondNucleotideBuffer) const;
	bool IsFull()const;
	unsigned int GetAmmount()const;
	NucleotideBuffer operator! ()const;
private:
	NucleotideStake current = 0;
	unsigned int nucleotideAmmount = 0;
};

