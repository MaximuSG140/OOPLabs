#include "TaskReadFile.h"
#include "RuntimeExceptions.h"
#include <fstream>
#include <string>
#include <vector>

void TaskReadFile::Complete(DataWrapper& shell, const std::vector<std::string>& arguments)const
{
	if(shell.isFilled)
	{
		throw InvalidDataCondition(true);
	}

	std::ifstream targetFile(arguments[0]);
	if(!targetFile)
	{
		throw InvalidFileName(arguments[0]);
	}

	shell.data = std::vector<std::string>();
	std::string str;
	while(std::getline(targetFile, str))
	{
		shell.data.push_back(str);
	}
	shell.isFilled = true;
}
