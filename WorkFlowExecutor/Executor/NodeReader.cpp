#include "NodeReader.h"
#include "RuntimeExceptions.h"

NodeReader& NodeReader::operator=(NodeReader&& other) noexcept
{
	taskMap = std::move(other.taskMap);
	instructionSequence = std::move(other.instructionSequence);
	return *this;
}

bool NodeReader::HasNodes() const
{
	return !instructionSequence.empty();
}

const Action& NodeReader::ReadNext()
{
	int number = instructionSequence.front();
	instructionSequence.pop();

	if(taskMap.count(number) == 0)
	{
		throw InvalidNodeNumber(number);
	}

	return taskMap[number];
}
