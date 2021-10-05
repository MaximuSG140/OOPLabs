// Executor.cpp : Определяет функции для статической библиотеки.
//
#include "Executor.h"
#include "FileSplitter.h"


Executor::Executor(const std::string& fileName)
{
	if(!FileSplitter::HasCorrectDescription(fileName))
	{
		throw std::exception();		//TODO: add a proper exception for this case
	}
	FileSplitter::GetBlockPart(fileName);
	FileSplitter::GetNodePart(fileName);
	if(!BlockReader::IsCorrect("BlockSequence.txt"))
	{
		throw std::exception();		//TODO: add a proper exception for this case
	}
	compiler = BlockReader("BlockSequence.txt");
	if (NodeReader::IsCorrect("NodeSequence.txt", compiler.ReadAllBlocks()))
	{
		throw std::exception();		//TODO: add a proper exception for this case
	}
	runner = NodeReader("NodeSequence.txt", compiler.ReadAllBlocks());
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
