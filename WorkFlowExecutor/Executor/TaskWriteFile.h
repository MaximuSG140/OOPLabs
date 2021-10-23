#pragma once
#include "Task.h"

class TaskWriteFile : public Task
{
public:
	void Complete(DataWrapper&, const std::vector<std::string>&)const override;
};
