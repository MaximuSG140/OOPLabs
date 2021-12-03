#pragma once
#include "Environment.h"
#include "EnvironmentQuery.h"

class RemoveApple final :
	public EnvironmentQuery
{
public:
	explicit RemoveApple(SmartRobot* collector);
	void Perform(Environment* env) override;
private:
	SmartRobot* collector_;
};

