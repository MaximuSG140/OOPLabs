#include "NodeReader.h"

NodeReader& NodeReader::operator=(NodeReader&& other) noexcept
{
	taskMap = std::move(other.taskMap);
	instructionSequence = std::move(other.instructionSequence);
	currentPosition = other.currentPosition;
	return *this;
}

bool NodeReader::HasNodes() const
{
	return currentPosition != instructionSequence.size();
}

Task* NodeReader::ReadNext()
{
	return taskMap[instructionSequence[currentPosition++]];
}

NodeReader::~NodeReader()
{
	for (auto& pair : taskMap)
	{
		delete pair.second;
	}
}
