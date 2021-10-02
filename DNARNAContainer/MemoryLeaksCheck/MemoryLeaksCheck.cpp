#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include "../DNARNAContainer/RNA.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	RNA r;
	for (int i = 0; i < 1000000; ++i)
	{
		r.AddNucleotide(static_cast<nucleotide>(i % 4));
	}
	_CrtDumpMemoryLeaks();
	return 0;
}