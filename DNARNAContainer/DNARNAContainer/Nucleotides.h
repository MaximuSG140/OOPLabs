#pragma once
typedef char NucleotideStake;

enum nucleotide : char {
	a, c, t, g
};

inline nucleotide Complimentary(const nucleotide n)
{
	switch (n)
	{
	case a:
		return t;
	case c: 
		return g;
	case t: 
		return a;
	case g: 
		return c;
	}
}
