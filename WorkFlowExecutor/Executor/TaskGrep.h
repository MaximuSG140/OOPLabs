#pragma once
#include "Task.h"
class TaskGrep : public Task
{
public:
	void Complete(DataWrapper&, const std::vector<std::string>&)const override;
};

