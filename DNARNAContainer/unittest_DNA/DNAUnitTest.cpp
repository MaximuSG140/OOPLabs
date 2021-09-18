#include "pch.h"
#include "../DNARNAContainer/DNA.h"

TEST(TestDNAMethods, TestTwoRNAConstructor)
{
	RNA r1(vector<nucleotide>{adenine, uracile, cytosine}), r2(vector<nucleotide>{uracile, adenine, guanine});
	bool wasException = false;
	try
	{
		DNA(r1, r2);
		r1[0] = guanine;
		DNA(r1, r2);
		
	}
	catch (RNAs_are_not_complimentary)
	{
		wasException = true;
	}
	EXPECT_EQ(true, wasException);
	wasException = false;
	try
	{
		r1[0] = adenine;
		DNA(r1, r2);

	}
	catch (RNAs_are_not_complimentary)
	{
		wasException = true;
	}
	EXPECT_EQ(false, wasException);
}