#include"Nucleotides.h"
#pragma once

class NuclBuffer
{
public:
	void AddNucl(Nucleotide newNucl);
	void RemoveLast();
	void Clear();
	NuclStake GetStake();
	NuclBuffer(int number, Nucleotide value);
private:
	NuclStake current = 0;
	int nuclAmmount = 0;
};

