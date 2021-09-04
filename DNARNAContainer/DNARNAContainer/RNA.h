#include <vector>
#include "Nucleotides.h"
#include "NuclBuffer.h"
#pragma once


class RNA
{
public:
	RNA();
	RNA(int capacity);
	RNA(int capacity, Nucleotide baseValue);
	//RNA(RNA r);
	~RNA();
	RNA operator+ (RNA r);
	RNA operator=  (RNA r);
	RNA operator! ();
	bool operator== (RNA r);
	bool operator!= (RNA r);
	bool IsComplimentary(RNA r);
	RNA operator[](int index);
	std::pair<RNA, RNA> Split(int index);
private:
	std::vector<NuclStake>storage;
	NuclBuffer buffer;
};

