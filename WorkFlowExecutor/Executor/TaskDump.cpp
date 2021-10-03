#include "TaskDump.h"
#include <fstream>
#include <string>

void TaskDump::Complete(std::vector<std::string>& data)
{
	std::ofstream targetFile(fileName);
	for(const auto& line : data)
	{
		targetFile << line << std::endl;
	}
}
