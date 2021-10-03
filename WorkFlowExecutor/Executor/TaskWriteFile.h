#pragma once
#include "Task.h"

class TaskWriteFile : public Task
{
public:
	void Complete(std::vector<std::string>&) override;
	TaskWriteFile(std::string fileName):fileName(std::move(fileName)){}
	~TaskWriteFile()override = default;
private:
	std::string fileName;
};
