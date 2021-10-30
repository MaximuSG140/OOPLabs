#include "Executor.h"
#include "FileParser.h"
#include "Tasks.h"


Executor::Executor(const std::string& fileName)
{
	taskGetter = {
		{operations::write, new TaskWriteFile()},
		{operations::replace, new TaskReplace()},
		{operations::sort, new TaskSort()},
		{operations::grep, new TaskGrep()},
		{operations::dump, new TaskDump()},
		{operations::read, new TaskReadFile()}};

	runner = NodeReader(
		FileParser::GetSequence(fileName),
		BlockReader::ReadAllBlocks(FileParser::GetBlocks(fileName), taskGetter));
}

void Executor::Run()
{
	DataWrapper shell;
	while (runner.HasNodes())
	{
		runner.ReadNext().Perform(shell);
	}
}

Executor::~Executor()
{
	for (auto element : taskGetter)
	{
		delete element.second;
	}
}
