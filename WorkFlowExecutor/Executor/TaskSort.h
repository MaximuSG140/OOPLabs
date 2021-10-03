#pragma once
#include "Task.h"

class TaskSort : public Task
{
public:
	TaskSort() = default;
	void Complete(std::vector<std::string>&) override;
	~TaskSort()override = default;
private:

};

