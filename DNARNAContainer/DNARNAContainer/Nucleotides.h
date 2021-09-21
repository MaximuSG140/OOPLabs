#pragma once
typedef char NucleotideStake;

enum nucleotide : char {
	 cytosine, adenine, thymine, guanine
};
constexpr  nucleotide uracile = thymine;

inline nucleotide GetComplimentaryNucleotide(const nucleotide n)
{
	return static_cast<nucleotide>((~n) & 3);
}
