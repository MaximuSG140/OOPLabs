#include "NodeReader.h"
#include <string>

bool NodeReader::HasNodes() const
{
	return !instructionStream.eof();
}

Task* NodeReader::ReadNext()
{
	int instruction;
	instructionStream >> instruction;
	std::string arrow;
	instructionStream >> arrow;
	return taskMap[instruction];
}

bool NodeReader::IsCorrect(const std::string& fileName, std::map<int, Task*>taskMap)
{
	std::string instructionNumber;
	std::ifstream targetFile(fileName);
	while(targetFile >> instructionNumber)
	{
		try
		{
			std::stoi(instructionNumber);
		}
		catch(std::exception&)
		{
			return false;	//incorrect number
		}
		try
		{
			taskMap[std::stoi(instructionNumber)];
		}
		catch(std::exception&)
		{
			return false;	//incorrect block number
		}
		std::string arrow;
		targetFile >> arrow;
		if(arrow != "->")
		{
			return false;	//incorrect instruction ptr
		}
	}
	return true;
}
