#pragma once
#include"RNA.h"


class DNA
{
public:
	DNA(const RNA& f, const RNA& s);
private:
	RNA firstChain, secondChain;
};

