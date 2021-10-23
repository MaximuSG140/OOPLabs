#pragma once
#include "Task.h"
#include <unordered_map>
#include <utility>
#include <queue>

struct Action
{
	Task* task = nullptr;
	std::vector<std::string> arguments;

	void Perform(DataWrapper& shell) const
	{
		task->Complete(shell, arguments);
	}

	Action() = default;
	Action(Task* task, std::vector<std::string> arguments):
		task(task),
		arguments(std::move(arguments)){}
};

class NodeReader
{
public:
	NodeReader() = default;
	NodeReader(std::queue<int> sequence, std::unordered_map<int, Action>taskMap):
		instructionSequence(std::move(sequence)),
		taskMap(std::move(taskMap)) {}

	NodeReader& operator=(NodeReader&&)noexcept;

	bool HasNodes() const;
	Action ReadNext();
private:
	std::queue<int> instructionSequence;
	std::unordered_map<int, Action> taskMap;
};

