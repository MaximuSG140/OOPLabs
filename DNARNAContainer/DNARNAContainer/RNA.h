#pragma once
#include <unordered_map>
#include "RNAExceptions.h"
#include "vector.h"
#include "Nucleotides.h"
#include "NucleotideBuffer.h"



class RNA
{
public:
	struct RNANucleotideReference
	{
		RNA *const This;
		unsigned int index;
		RNANucleotideReference(RNA *const This, const unsigned int index):This(This), index(index){}
		RNANucleotideReference& operator=(nucleotide value);
		RNANucleotideReference& operator=(const RNANucleotideReference& other);
		operator const nucleotide() const;
	};

	RNA();
	explicit RNA(const vector<nucleotide>& chain);
	explicit RNA(const vector<nucleotide>&& chain);
	explicit RNA(int capacity);
	explicit RNA(int capacity, nucleotide baseValue);
	RNA(const RNA& r);
	RNA(const RNA&& r);
	~RNA();

	unsigned int GetSize()const;
	unsigned int GetLength()const;
	unsigned int GetCapacity()const;
	unsigned int GetCardinality(const nucleotide example)const;
	std::unordered_map<nucleotide, int, std::hash<int>>GetCardinality()const;
	void AddNucleotide(nucleotide n);
	RNA Trim(unsigned int lastIndex);
	bool IsComplimentary(const RNA& r)const;
	std::pair<RNA, RNA> Split(const unsigned int index) const;

	RNA operator+ (const RNA& r) const;
	RNA& operator=  (const RNA& r);
	RNA& operator= (RNA&& r);
	RNA operator! () const;
	bool operator== (const RNA& r)const;
	bool operator!= (const RNA& r)const;
	RNANucleotideReference operator[](const unsigned int index);
private:
	void PushBuffer();
	vector<NucleotideStake>storage;
	NucleotideBuffer buffer;
};


