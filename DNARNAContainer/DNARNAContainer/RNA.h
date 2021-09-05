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
	void AddNucleotide(nucleotide n);
	void PushBuffer();
	RNA& operator+ (const RNA& r) const;
	RNA& operator=  (const RNA& r);
	RNA& operator! () const;
	bool operator== (const RNA& r)const;
	bool operator!= (const RNA& r)const;
	bool IsComplimentary(RNA r);
	nucleotide operator[](unsigned int index)const;
	std::pair<RNA, RNA> Split(int index);
private:
	std::vector<NucleotideStake>storage;
	NucleotideBuffer buffer;
};


