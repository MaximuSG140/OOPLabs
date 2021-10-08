#include "NodeReader.h"

void NodeReader::DeleteTasks()
{
	for (auto pair : taskMap)
	{
		delete pair.second;
	}
}

bool NodeReader::HasNodes() const
{
	return currentPosition != instructionSequence.size();
}

Task* NodeReader::ReadNext()
{
	return taskMap[instructionSequence[currentPosition++]];
}
