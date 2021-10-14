#pragma once
#include "NodeReader.h"
#include "BlockReader.h"

class Executor
{
public:
	explicit Executor(const std::string&);
	void Run();

	~Executor() = default;
private:
	NodeReader runner;
};
