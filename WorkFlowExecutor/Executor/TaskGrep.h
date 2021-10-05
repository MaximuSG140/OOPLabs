#pragma once
#include "Task.h"
class TaskGrep : public Task
{
public:
	void Complete(std::vector<std::string>&) override;
	TaskGrep(std::string keyWord):keyWord(std::move(keyWord)){}
private:
	std::string keyWord;
};

