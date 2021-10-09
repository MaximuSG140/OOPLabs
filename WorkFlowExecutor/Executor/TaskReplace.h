#pragma once
#include "Task.h"


class TaskReplace : public Task
{
public:
	void Complete(DataWrapper&) override;
	TaskReplace(std::string keyWord, std::string toChange):keyWord(std::move(keyWord)), toChange(std::move(toChange)){}
private:
	std::string keyWord, toChange;
};

