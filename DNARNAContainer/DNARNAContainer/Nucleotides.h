#pragma once
typedef char NucleotideStake;

enum nucleotide : char {
	adenine, cytosine, thymine, guanine
};

inline nucleotide GetComplimentaryNucleotide(const nucleotide n)
{
	switch (n)
	{
	case adenine:
		return thymine;
	case cytosine: 
		return guanine;
	case thymine: 
		return adenine;
	case guanine: 
		return cytosine;
	}
}
