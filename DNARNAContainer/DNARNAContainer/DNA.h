#pragma once
#include"RNA.h"
#include "DNAExceptions.h"

class DNA
{
public:
	DNA(const RNA& f, const RNA& s);
private:
	RNA firstChain, secondChain;
};

