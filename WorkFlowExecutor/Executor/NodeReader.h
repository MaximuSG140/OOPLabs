#pragma once
#include "Task.h"
#include <map>
#include <utility>

class NodeReader
{
public:
	NodeReader() = default;
	NodeReader(std::vector<int> sequence, std::map<int, std::shared_ptr<Task> >taskMap)
		:instructionSequence(std::move(sequence)), taskMap(std::move(taskMap)) {}

	NodeReader& operator=(NodeReader&&)noexcept;

	bool HasNodes() const;
	std::shared_ptr<Task> ReadNext();

	~NodeReader() = default;
private:
	size_t currentPosition = 0;
	std::vector<int> instructionSequence;
	std::map<int, std::shared_ptr<Task>>taskMap;
};

