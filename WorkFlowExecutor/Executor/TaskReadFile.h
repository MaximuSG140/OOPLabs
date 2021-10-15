#pragma once
#include <vector>
#include "Task.h"

class TaskReadFile : public Task
{
public:
	void Complete(DataWrapper&) override;
	TaskReadFile(std::string fileName):
		fileName(std::move(fileName)) {}
private:
	std::string fileName;
};

