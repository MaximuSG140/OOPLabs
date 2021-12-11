#include "RemoveRobot.h"

RemoveRobot::RemoveRobot(SmartRobot* removed_robot) :
	removed_(removed_robot)
{}

void RemoveRobot::Perform(Environment* env)
{
	env->RemoveRobot(removed_);
}
