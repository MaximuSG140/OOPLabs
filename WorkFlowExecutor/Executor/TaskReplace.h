#pragma once
#include "Task.h"


class TaskReplace : public Task
{
public:
	void Complete(DataWrapper&, const std::vector<std::string>& arguments)const override;
};

