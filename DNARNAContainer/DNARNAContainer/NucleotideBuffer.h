#pragma once
#include"Nucleotides.h"

class NucleotideBuffer
{
public:
	void AddNucleotide(nucleotide newNucleotide);
	void RemoveLast();
	void Clear();
	NucleotideStake GetStake() const;
	NucleotideBuffer();
	NucleotideBuffer(int number, nucleotide value);
private:
	NucleotideStake current = 0;
	int nucleotideAmmount = 0;
};

