// Executor.cpp : Определяет функции для статической библиотеки.
//
#include "Executor.h"


Executor::Executor(std::string fileName)
{
	compiler = BlockReader(FileSplitter::GetBlockPart(fileName));
	runner = NodeReader(FileSplitter::GetNodePart(fileName), compiler.ReadAllBlocks());
}

void Executor::Run()
{
	std::vector<std::string> data;
	while (runner.HasNodes())
	{
		Task* currentTask = runner.ReadNext();
		currentTask->Complete(data);
		delete currentTask;
	}
}
