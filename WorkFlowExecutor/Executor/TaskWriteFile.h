#pragma once
#include "Task.h"

class TaskWriteFile : public Task
{
public:
	void Complete(DataWrapper&) override;
	TaskWriteFile(std::string fileName):
		fileName(std::move(fileName)){}
private:
	std::string fileName;
};
