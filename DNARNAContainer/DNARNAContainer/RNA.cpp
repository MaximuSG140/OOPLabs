#include "RNA.h"

RNA::RNA(){}

RNA::RNA(int capacity)
{
	storage = std::vector<NuclStake>(capacity/4);
}

RNA::RNA(int capacity, Nucleotide baseValue)
{
	storage = std::vector<NuclStake>(capacity / 4, NuclBuffer(4, baseValue).GetStake());
	buffer = NuclBuffer(capacity % 4, baseValue);
}

RNA::~RNA(){}
