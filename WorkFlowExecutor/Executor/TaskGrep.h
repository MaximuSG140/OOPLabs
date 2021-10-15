#pragma once
#include "Task.h"
class TaskGrep : public Task
{
public:
	void Complete(DataWrapper&) override;
	TaskGrep(std::string keyWord):
		keyWord(std::move(keyWord)){}
private:
	std::string keyWord;
};

