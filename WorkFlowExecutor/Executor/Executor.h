#pragma once
#include "NodeReader.h"
#include "BlockReader.h"

class Executor
{
public:
	Executor(const std::string& fileName);
	void Run();

	~Executor();
private:
	NodeReader runner;
};
