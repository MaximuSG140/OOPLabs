#pragma once
#include <vector>
#include "Task.h"

class TaskReadFile : public Task
{
public:
	void Complete(std::vector<std::string>&) override;
	TaskReadFile(std::string fileName) :fileName(std::move(fileName)) {}
private:
	std::string fileName;
};

