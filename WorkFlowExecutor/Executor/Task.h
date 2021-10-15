#pragma once
#include "DataWrapper.h"

class Task
{
public:
	virtual void Complete(DataWrapper&)=0;
	virtual ~Task() = default;
};