#include "TaskWriteFile.h"
#include <fstream>
#include <string>

void TaskWriteFile::Complete(DataWrapper& shell)
{
	if(shell.isFilled == false)
	{
		throw invalid_data_condition(false);
	}
	std::ofstream targetFile(fileName);
	for(const auto& line : shell.data)
	{
		targetFile << line << std::endl;
	}
	shell.isFilled = false;
	targetFile.close();
}
