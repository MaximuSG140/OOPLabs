#pragma once
#include <unordered_map>
#include <vector>
#include "Nucleotides.h"
#include "NucleotideBuffer.h"

class RNA
{
public:
	RNA();
	RNA(const std::vector<nucleotide>& chain);
	explicit RNA(int capacity);
	explicit RNA(int capacity, nucleotide baseValue);
	RNA(const RNA& r);
	~RNA();

	unsigned int GetCapacity()const ;
	unsigned int GetCardinality(const nucleotide example)const;
	std::unordered_map<nucleotide, int, std::hash<int>>GetCardinality()const;
	void AddNucleotide(nucleotide n);
	void Trim(unsigned int index);
	bool IsComplimentary(const RNA& r)const;
	std::pair<RNA, RNA> Split(const int index) const;

	RNA operator+ (const RNA& r) const;
	RNA& operator=  (const RNA& r);
	RNA& operator= (RNA&& r);
	RNA operator! () const;
	bool operator== (const RNA& r)const;
	bool operator!= (const RNA& r)const;
	nucleotide operator[](const unsigned int index)const;
private:
	void PushBuffer();
	std::vector<NucleotideStake>storage;
	NucleotideBuffer buffer;
};


