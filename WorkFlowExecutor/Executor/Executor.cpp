﻿#include "Executor.h"
#include "FileParser.h"
#include "ParseExceptions.h"


Executor::Executor(const std::string& fileName)
{
	if(!FileParser::HasCorrectDescription(fileName))
	{
		throw invalid_description_block(fileName);
	}
	runner = NodeReader(FileParser::GetSequence(fileName), BlockReader::ReadAllBlocks(FileParser::GetBlocks(fileName)));
}

void Executor::Run()
{
	DataWrapper shell;
	while (runner.HasNodes())
	{
		Task* currentTask = runner.ReadNext();
		currentTask->Complete(shell);
	}
}
