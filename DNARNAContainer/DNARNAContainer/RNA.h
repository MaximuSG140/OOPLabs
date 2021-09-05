#pragma once
#include <vector>
#include "Nucleotides.h"
#include "NucleotideBuffer.h"

class RNA
{
public:
	RNA();
	explicit RNA(int capacity);
	explicit RNA(int capacity, nucleotide baseValue);
	explicit RNA(RNA& r);
	~RNA();
	RNA& operator+ (RNA r);
	RNA& operator=  (const RNA& r);
	RNA& operator! ();
	bool operator== (RNA r);
	bool operator!= (RNA r);
	bool IsComplimentary(RNA r);
	nucleotide operator[](unsigned int index)const;
	std::pair<RNA, RNA> Split(int index);
private:
	std::vector<NucleotideStake>storage;
	NucleotideBuffer buffer;
};


