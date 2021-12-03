#pragma once
#include "Environment.h"
#include "EnvironmentQuery.h"

class RemoveRobot final :
	public EnvironmentQuery
{
public:
	explicit RemoveRobot(SmartRobot* removed_robot);

	void Perform(Environment* env) override;
private:
	SmartRobot* removed_;
};

