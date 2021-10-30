#pragma once
#include "Task.h"

class TaskDump : public Task
{
public:
	void Complete(DataWrapper&, const std::vector<std::string>&)const override;
};