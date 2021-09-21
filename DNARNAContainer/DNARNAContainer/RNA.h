#pragma once
#include <unordered_map>
#include "RNAExceptions.h"
#include "vector.h"
#include "Nucleotides.h"
#include "NucleotideBuffer.h"



class RNA
{
public:
	class NucleotideReference
	{
	public:
		NucleotideReference(RNA *const This, const unsigned int index):This(This), index(index){}
		NucleotideReference& operator=(nucleotide value);
		NucleotideReference& operator=(const NucleotideReference& other);
		operator const nucleotide() const;
	private:
		RNA *const This;
		unsigned int index;
	};

	RNA();
	explicit RNA(const vector<nucleotide>& chain);
	explicit RNA(const vector<nucleotide>&& chain);
	explicit RNA(int capacity, nucleotide baseValue = static_cast<nucleotide>(0));
	RNA(const RNA& r);
	RNA(const RNA&& r);
	~RNA();

	unsigned int GetSize()const;
	unsigned int GetLength()const;
	unsigned int GetCapacity()const;
	unsigned int GetCardinality(nucleotide example)const;
	std::unordered_map<nucleotide, int, std::hash<int>>GetCardinality()const;
	void AddNucleotide(nucleotide n);
	RNA Trim(unsigned int lastIndex);
	bool IsComplimentary(const RNA& r)const;
	std::pair<RNA, RNA> Split(unsigned int index) const;

	RNA operator+ (const RNA& r) const;
	RNA& operator=  (const RNA& r);
	RNA& operator= (RNA&& r);
	RNA operator! () const;
	bool operator== (const RNA& r)const;
	bool operator!= (const RNA& r)const;
	NucleotideReference operator[](unsigned int index);
private:
	void PushBuffer();
	vector<NucleotideStake>storage;
	NucleotideBuffer buffer;
};


