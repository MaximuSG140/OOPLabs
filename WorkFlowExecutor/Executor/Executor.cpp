// Executor.cpp : Определяет функции для статической библиотеки.
//
#include "Executor.h"
#include "FileParser.h"


Executor::Executor(const std::string fileName)
{
	if(!FileParser::HasCorrectDescription(fileName))
	{
		throw std::exception();		//TODO: add a proper exception for this case
	}
	runner = NodeReader(FileParser::GetSequence(fileName), BlockReader::ReadAllBlocks(FileParser::GetBlocks(fileName)));
}

void Executor::Run()
{
	std::vector<std::string> data;
	while (runner.HasNodes())
	{
		Task* currentTask = runner.ReadNext();
		currentTask->Complete(data);
	}
}

Executor::~Executor()
{
	runner.DeleteTasks();
}
