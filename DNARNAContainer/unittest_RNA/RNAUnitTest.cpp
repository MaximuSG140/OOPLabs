#include "pch.h"
#include "../DNARNAContainer/RNA.h"

TEST(TestRNAMethods, TestGetCapacity)
{
	EXPECT_EQ(0, RNA().GetCapacity());
	EXPECT_EQ(4, RNA(4, adenine).GetCapacity());
	EXPECT_EQ(1, RNA(1, cytosine).GetCapacity());
	EXPECT_EQ(11, RNA(11).GetCapacity());
}

TEST(TestRNAMethods, TestGetCardinality)
{
	EXPECT_EQ(0, RNA().GetCardinality()[adenine]);
	EXPECT_EQ(0, RNA().GetCardinality(adenine));
	EXPECT_EQ(12, RNA(12, thymine).GetCardinality(thymine));
	EXPECT_EQ(0, RNA(12, thymine).GetCardinality(adenine));
	RNA testExample;
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(guanine);
	testExample.AddNucleotide(guanine);
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(thymine);
	EXPECT_EQ(0, testExample.GetCardinality(cytosine));
	EXPECT_EQ(5, testExample.GetCardinality(adenine));
	EXPECT_EQ(1, testExample.GetCardinality(thymine));
	EXPECT_EQ(2, testExample.GetCardinality(guanine));
	EXPECT_EQ(0, testExample.GetCardinality()[cytosine]);
	EXPECT_EQ(5, testExample.GetCardinality()[adenine]);
	EXPECT_EQ(1, testExample.GetCardinality()[thymine]);
	EXPECT_EQ(2, testExample.GetCardinality()[guanine]);
}

TEST(TestRNAMethods, TestOperatorSum)
{
	EXPECT_EQ(RNA(10), RNA(5) + RNA(5));
	EXPECT_EQ(RNA(), RNA() + RNA());
	EXPECT_EQ(RNA(3, cytosine), RNA(2, cytosine) + RNA(1, cytosine));
	EXPECT_EQ(RNA(3, adenine) + RNA(2, adenine), RNA(2, adenine) + RNA(3, adenine));

	RNA testExample;
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(guanine);
	testExample.AddNucleotide(guanine);
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(thymine);
	EXPECT_EQ(testExample, RNA(3, adenine) + RNA(2, guanine) + RNA(2, adenine) + RNA(1, thymine));
}

TEST(TestRNAMethods, testVectorConstructor)
{
	vector<nucleotide> chain({ adenine, guanine, thymine, cytosine, cytosine, cytosine });
	RNA r(vector<nucleotide>({ adenine, guanine, thymine, cytosine, cytosine, cytosine }));
	EXPECT_EQ(adenine, r[0]);
	EXPECT_EQ(guanine, r[1]);
	EXPECT_EQ(thymine, r[2]);
	EXPECT_EQ(cytosine, r[3]);
	EXPECT_EQ(cytosine, r[4]);
	EXPECT_EQ(cytosine, r[5]);
}

TEST(TestRNAMethods, testSameElementConstructor)
{
	RNA r(10, adenine);
	for(int i = 0; i < 10; i++)
	{
		EXPECT_EQ(adenine, r[i]);
	}
	r = RNA(10, thymine);
	for (int i = 0; i < 10; i++)
	{
		EXPECT_EQ(thymine, r[i]);
	}
	r = RNA(10, guanine);
	for (int i = 0; i < 10; i++)
	{
		EXPECT_EQ(guanine, r[i]);
	}
	r = RNA(10, cytosine);
	for (int i = 0; i < 10; i++)
	{
		EXPECT_EQ(cytosine, r[i]);
	}
}

TEST(TestRNAMethods, TestOperatorIsEqual)
{
	EXPECT_EQ(true, RNA({ adenine, cytosine, cytosine, thymine, adenine }) == RNA({ adenine, cytosine, cytosine, thymine, adenine }));
	EXPECT_EQ(false, RNA() == RNA(1));
	EXPECT_EQ(true, RNA() == RNA());
	EXPECT_EQ(false, RNA({ adenine, thymine, cytosine }) == RNA({ cytosine, thymine, guanine }));
	EXPECT_EQ(true, RNA(5, adenine) == RNA(5, adenine));
	EXPECT_EQ(false, RNA(5, guanine) == RNA(5, adenine));
}

TEST(TestRNAMethods, TestOperatorIsComplimentary)
{
	EXPECT_EQ(true, RNA(1, adenine ).IsComplimentary(RNA(1, thymine )));
	EXPECT_EQ(false, RNA(1, adenine).IsComplimentary(RNA(1, adenine)));
	EXPECT_EQ(false, RNA(1, adenine).IsComplimentary(RNA(1, guanine )));
	EXPECT_EQ(false, RNA(1, adenine).IsComplimentary(RNA(1, cytosine)));
	EXPECT_EQ(false, RNA(1, thymine).IsComplimentary(RNA(1, thymine)));
	EXPECT_EQ(true, RNA(1, thymine).IsComplimentary(RNA(1, adenine)));
	EXPECT_EQ(false, RNA(1, thymine).IsComplimentary(RNA(1, guanine)));
	EXPECT_EQ(false, RNA(1, thymine).IsComplimentary(RNA(1, cytosine)));
	EXPECT_EQ(false, RNA(1, cytosine ).IsComplimentary(RNA(1, thymine)));
	EXPECT_EQ(false, RNA(1, cytosine).IsComplimentary(RNA(1, adenine)));
	EXPECT_EQ(true, RNA(1, cytosine).IsComplimentary(RNA(1, guanine)));
	EXPECT_EQ(false, RNA(1, cytosine).IsComplimentary(RNA(1, cytosine)));
	EXPECT_EQ(false, RNA(1, guanine).IsComplimentary(RNA(1, thymine)));
	EXPECT_EQ(false, RNA(1, guanine).IsComplimentary(RNA(1, adenine)));
	EXPECT_EQ(false, RNA(1, guanine).IsComplimentary(RNA(1, guanine)));
	EXPECT_EQ(true, RNA(1, guanine).IsComplimentary(RNA(1, cytosine)));
	EXPECT_EQ(false, RNA({ adenine, thymine, cytosine, guanine }).IsComplimentary(RNA({ thymine, adenine, adenine, cytosine })));
	EXPECT_EQ(true, RNA({ adenine, thymine, cytosine, guanine }).IsComplimentary(RNA({ thymine, adenine, guanine, cytosine })));
}

TEST(TestRNAMethods, TestAddNucleotide)
{
	RNA r;
	r.AddNucleotide(adenine);
	r.AddNucleotide(adenine);
	r.AddNucleotide(thymine);
	r.AddNucleotide(cytosine);
	r.AddNucleotide(adenine);
	EXPECT_EQ(r, RNA({ adenine, adenine, thymine, cytosine, adenine }));
	EXPECT_EQ(5, r.GetCapacity());
	EXPECT_EQ(3, r.GetCardinality(adenine));
	EXPECT_EQ(1, r.GetCardinality(thymine));
	EXPECT_EQ(1, r.GetCardinality(cytosine));
	EXPECT_EQ(0, r.GetCardinality(guanine));
	r.AddNucleotide(guanine);
	EXPECT_EQ(r, RNA({ adenine, adenine, thymine, cytosine, adenine, guanine }));
	EXPECT_EQ(6, r.GetCapacity());
	EXPECT_EQ(3, r.GetCardinality(adenine));
	EXPECT_EQ(1, r.GetCardinality(thymine));
	EXPECT_EQ(1, r.GetCardinality(cytosine));
	EXPECT_EQ(1, r.GetCardinality(guanine));
}

TEST(TestRNAMethods, TestSplit)
{
	EXPECT_EQ(RNA({ adenine, cytosine, adenine, adenine }), RNA({ adenine, cytosine, adenine, adenine, adenine, thymine }).Split(3).first);
	EXPECT_EQ(RNA({ adenine, thymine, guanine}), RNA({ adenine, adenine, thymine, guanine}).Split(0).second);
}

TEST(TestRNAMethods, TestOperatorIsNotEqual)
{
	EXPECT_EQ(false, RNA({ adenine, cytosine, cytosine, thymine, adenine }) != RNA({ adenine, cytosine, cytosine, thymine, adenine }));
	EXPECT_EQ(true, RNA() != RNA(1));
	EXPECT_EQ(false, RNA() != RNA());
	EXPECT_EQ(true, RNA({ adenine, thymine, cytosine }) != RNA({ cytosine, thymine, guanine }));
	EXPECT_EQ(false, RNA(5, adenine) != RNA(5, adenine));
	EXPECT_EQ(true, RNA(5, guanine) != RNA(5, adenine));
}

TEST(TestRNAMethods, TestOperatorInvert)
{
	EXPECT_EQ(RNA(1, adenine), !RNA(1, thymine));
	EXPECT_EQ(RNA({ adenine, cytosine, thymine, guanine }), !RNA({ thymine, guanine, adenine, cytosine }));
	EXPECT_EQ(true, RNA().IsComplimentary(!RNA()));
	EXPECT_EQ(true, RNA({ adenine, guanine, adenine, guanine }).IsComplimentary(!RNA({ adenine, guanine, adenine, guanine })));
}

TEST(TestRNAMethods, TestOperatorAssign)
{
	EXPECT_EQ(RNA(), RNA(10, adenine) = RNA());
	RNA r;
	r.AddNucleotide(adenine);
	r.AddNucleotide(thymine);
	r.AddNucleotide(adenine);
	RNA testExample = r;
	EXPECT_EQ(RNA({ adenine, thymine, adenine }), testExample);
	EXPECT_EQ(RNA({ guanine, thymine, cytosine }), RNA({ guanine, adenine, guanine }) = RNA({ guanine, thymine, cytosine }));
	testExample = RNA({ cytosine, thymine, adenine });
	EXPECT_EQ(RNA({ cytosine, thymine, adenine }), testExample);
}

TEST(TestRNAMethods, TestIndexator)
{
	RNA testExample;
	testExample.AddNucleotide(adenine);
	testExample.AddNucleotide(cytosine);
	testExample.AddNucleotide(guanine);
	testExample.AddNucleotide(thymine);
	testExample.AddNucleotide(thymine);
	EXPECT_EQ(adenine, testExample[0]);
	EXPECT_EQ(cytosine, testExample[1]);
	EXPECT_EQ(guanine, testExample[2]);
	EXPECT_EQ(thymine, testExample[3]);
	EXPECT_EQ(thymine, testExample[4]);
	testExample = RNA(vector<nucleotide>{ adenine, cytosine, guanine, thymine, thymine });
	EXPECT_EQ(adenine, testExample[0]);
	EXPECT_EQ(cytosine, testExample[1]);
	EXPECT_EQ(guanine, testExample[2]);
	EXPECT_EQ(thymine, testExample[3]);
	EXPECT_EQ(thymine, testExample[4]);
}

TEST(TestRNAMethods, TestTrim)
{
	EXPECT_EQ(RNA(vector<nucleotide>{ adenine}), RNA({ adenine, cytosine, thymine, adenine, thymine }).Trim(0));
	EXPECT_EQ(RNA(vector<nucleotide>{ adenine, cytosine}), RNA({ adenine, cytosine, thymine, adenine, thymine }).Trim(1));
	EXPECT_EQ(RNA({ adenine, cytosine, thymine }), RNA({ adenine, cytosine, thymine, adenine, thymine }).Trim(2));
	EXPECT_EQ(RNA({ adenine, cytosine, thymine, adenine }), RNA({ adenine, cytosine, thymine, adenine, thymine }).Trim(3));
	EXPECT_EQ(RNA({ adenine, cytosine, thymine, adenine, thymine }), RNA({ adenine, cytosine, thymine, adenine, thymine }).Trim(4));
}

