#pragma once
#include "DataWrapper.h"
#include <vector>
#include <string>

class Task
{
public:
	virtual void Complete(DataWrapper&, const std::vector<std::string>&) const =0;
	virtual ~Task() = default;
};