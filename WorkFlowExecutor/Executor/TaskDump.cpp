#include "TaskDump.h"
#include <fstream>
#include <string>

void TaskDump::Complete(DataWrapper& shell)
{
	if(!shell.isFilled)
	{
		throw invalid_data_condition(false);
	}
	std::ofstream targetFile(fileName);
	for(const auto& line : shell.data)
	{
		targetFile << line << std::endl;
	}
}
