#pragma once
#include "EnvironmentQuery.h"

class Environment;
class SmartRobot;

class SetSurroundingsInfo final :
	public EnvironmentQuery
{
public:
	explicit SetSurroundingsInfo(SmartRobot* scanner);
	void Perform(Environment* env) override;
private:
	SmartRobot* op_robot_;
};

