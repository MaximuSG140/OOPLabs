#pragma once
#include "Task.h"
#include <unordered_map>
#include <memory>
#include <utility>
#include <queue>

class NodeReader
{
public:
	NodeReader() = default;
	NodeReader(std::queue<int> sequence, std::unordered_map<int, Task*>taskMap):
		instructionSequence(std::move(sequence)),
		taskMap(std::move(taskMap)) {}

	NodeReader& operator=(NodeReader&&)noexcept;

	bool HasNodes() const;
	Task* ReadNext();

	~NodeReader();
private:
	std::queue<int> instructionSequence;
	std::unordered_map<int, Task*> taskMap;
};

