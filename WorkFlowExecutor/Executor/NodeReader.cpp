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

Task* NodeReader::ReadNext()
{
	int number = instructionSequence.front();
	instructionSequence.pop();

	if(taskMap.count(number) == 0)
	{
		throw invalid_node_number(number);
	}

	return taskMap[number];
}

NodeReader::~NodeReader()
{
	for (auto& pair : taskMap)
	{
		delete pair.second;
	}
}
