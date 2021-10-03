#pragma once
#include <vector>

class Task
{
private:
public:
	virtual void Complete(std::vector<std::string>&)=0;
	virtual ~Task()=0;
};

