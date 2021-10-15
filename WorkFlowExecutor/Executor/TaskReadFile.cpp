#include "TaskReadFile.h"
#include "RuntimeExceptions.h"
#include <fstream>
#include <string>
#include <vector>

void TaskReadFile::Complete(DataWrapper& shell)
{
	if(shell.isFilled)
	{
		throw invalid_data_condition(true);
	}
	std::ifstream targetFile(fileName);
	if(!targetFile)
	{
		throw invalid_file_name(fileName);
	}
	shell.data = std::vector<std::string>();
	std::string str;
	while(std::getline(targetFile, str))
	{
		shell.data.push_back(str);
	}
	shell.isFilled = true;
}
