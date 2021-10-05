#pragma once
#include "Task.h"

class TaskDump : public Task
{
public:
	void Complete(std::vector<std::string>&) override;
	TaskDump(std::string fileName):fileName(std::move(fileName)){}
private:
	std::string fileName;
};

