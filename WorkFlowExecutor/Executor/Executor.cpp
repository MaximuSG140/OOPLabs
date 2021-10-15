#include "Executor.h"
#include "FileParser.h"


Executor::Executor(const std::string& fileName)
{
	runner = NodeReader(
		FileParser::GetSequence(fileName),
		BlockReader::ReadAllBlocks(FileParser::GetBlocks(fileName)));
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
