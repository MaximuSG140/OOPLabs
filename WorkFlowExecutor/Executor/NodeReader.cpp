#include "NodeReader.h"
#include <string>

NodeReader::~NodeReader()
{
	delete instructionStream;
}

bool NodeReader::HasNodes()
{
	return instructionStream->eof();
}

Task* NodeReader::ReadNext()
{
	std::string instructionNumber;
	*instructionStream >> instructionNumber;
	int instruction = std::stoi(instructionNumber);
	std::string arrow;
	*instructionStream >> arrow;
	return taskMap[instruction];
}
