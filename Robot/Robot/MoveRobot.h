#pragma once
#include "EnvironmentQuery.h"


enum class Direction;
class SmartRobot;

class MoveRobot final :
	public EnvironmentQuery
{
public:
	explicit MoveRobot(Direction move_direction, SmartRobot* moving_robot);
	void Perform(Environment* env) override;
private:
	SmartRobot* operating_robot_;
	Direction move_direction_;
};

