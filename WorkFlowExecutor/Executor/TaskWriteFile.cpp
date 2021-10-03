#include "TaskWriteFile.h"
#include <fstream>
#include <string>

void TaskWriteFile::Complete(std::vector<std::string>& data)
{
	std::ofstream targetFile(fileName);
	for(const auto& line : data)
	{
		targetFile << line << std::endl;
	}
	targetFile.close();
}
