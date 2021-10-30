#include "TaskDump.h"
#include <fstream>
#include <string>
#include "RuntimeExceptions.h"

void TaskDump::Complete(DataWrapper& shell, const std::vector<std::string>& arguments)const
{
	if(!shell.isFilled)
	{
		throw InvalidDataCondition(false);
	}

	std::ofstream targetFile(arguments[0]);
	for(const auto& line : shell.data)
	{
		targetFile << line << std::endl;
	}
}
