#pragma once
#include "Task.h"
#include <map>
#include <memory>
#include <utility>

class NodeReader
{
public:
	NodeReader() = default;
	NodeReader(std::vector<int> sequence, std::map<int, Task*>taskMap)
		:instructionSequence(std::move(sequence)), taskMap(std::move(taskMap)) {}

	NodeReader& operator=(NodeReader&&)noexcept;

	bool HasNodes() const;
	Task* ReadNext();

	~NodeReader();
private:
	size_t currentPosition = 0;
	std::vector<int> instructionSequence;
	std::map<int, Task*>taskMap;
};

