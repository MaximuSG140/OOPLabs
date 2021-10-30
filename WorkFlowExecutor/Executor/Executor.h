#pragma once
#include "NodeReader.h"
#include "BlockReader.h"

class Executor
{
public:
	explicit Executor(const std::string&);
	void Run();

	Executor(Executor&) = delete;
	Executor& operator=(Executor&) = delete;

	~Executor();
private:
	std::unordered_map<operations, Task*> taskGetter;
	NodeReader runner;
};
