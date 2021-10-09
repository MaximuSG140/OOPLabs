#pragma once
#include "Task.h"

class TaskSort : public Task
{
public:
	TaskSort() = default;
	void Complete(DataWrapper&) override;
private:

};

