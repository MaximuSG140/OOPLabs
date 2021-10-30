#include "TaskWriteFile.h"
#include <fstream>
#include <string>
#include "RuntimeExceptions.h"

void TaskWriteFile::Complete(DataWrapper& shell, const std::vector<std::string>& arguments)const
{
	if(shell.isFilled == false)
	{
		throw InvalidDataCondition(false);
	}

	std::ofstream targetFile(arguments[0]);
	for(const auto& line : shell.data)
	{
		targetFile << line << std::endl;
	}
	shell.isFilled = false;
}
