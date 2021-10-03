#pragma once
#include "Task.h"


class TaskReplace : public Task
{
public:
	void Complete(std::vector<std::string>&) override;
	TaskReplace(std::string keyWord, std::string toChange):keyWord(std::move(keyWord)), toChange(std::move(toChange)){}
	~TaskReplace()override = default;
private:
	std::string keyWord, toChange;
};

