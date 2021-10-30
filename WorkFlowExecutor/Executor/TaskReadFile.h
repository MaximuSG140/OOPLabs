#pragma once
#include <vector>
#include "Task.h"

class TaskReadFile : public Task
{
public:
	void Complete(DataWrapper&, const std::vector<std::string>&)const override;
};

