#pragma once
#include <vector>
#include "Nucleotides.h"
#include "NucleotideBuffer.h"

class RNA
{
public:
	RNA();
	RNA(int capacity);
	RNA(int capacity, nucleotide baseValue);
	//RNA(RNA r);
	~RNA();
	RNA operator+ (RNA r);
	RNA& operator=  (const RNA& r);
	RNA operator! ();
	bool operator== (RNA r);
	bool operator!= (RNA r);
	bool IsComplimentary(RNA r);
	RNA operator[](int index);
	std::pair<RNA, RNA> Split(int index);
private:
	std::vector<NucleotideStake>storage;
	NucleotideBuffer buffer;
};

