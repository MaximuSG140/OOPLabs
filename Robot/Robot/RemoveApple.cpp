#include "RemoveApple.h"

RemoveApple::RemoveApple(SmartRobot* collector) :
	collector_(collector)
{}

void RemoveApple::Perform(Environment* env)
{
	RobotInfo& apple_collector_info = env->GetRobotInfo(collector_);
	env->GetMap().RemoveApple(apple_collector_info.position);
}
