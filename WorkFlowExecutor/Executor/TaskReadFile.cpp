#include "TaskReadFile.h"
#include <fstream>
#include <string>
#include <vector>

void TaskReadFile::Complete(std::vector<std::string>& data)
{
	std::ifstream targetFile(fileName);
	data = std::vector<std::string>();
	std::string str;
	while(std::getline(targetFile, str))
	{
		data.push_back(str);
	}
	targetFile.close();
}
