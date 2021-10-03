#pragma once
#include "NodeReader.h"
#include "BlockReader.h"
#include "FileSplitter.h"

class Executor
{
public:
	Executor(std::string fileName);
	void Run();
private:
	NodeReader runner;
	BlockReader compiler;
};
