#include "SetSurroundingsInfo.h"
#include "SmartRobot.h"
#include "Environment.h"

SetSurroundingsInfo::SetSurroundingsInfo(SmartRobot* scanner) :
	op_robot_(scanner)
{}

void SetSurroundingsInfo::Perform(Environment* env)
{
	RobotInfo& scanner_info = env->GetRobotInfo(op_robot_);
	ScaleMap cached_map = op_robot_->GetMap();
	cached_map[op_robot_->GetPosition()] = env->GetMap()[scanner_info.position];
	cached_map[op_robot_->GetPosition().Left()] = env->GetMap()[scanner_info.position.Left()];
	cached_map[op_robot_->GetPosition().Right()] = env->GetMap()[scanner_info.position.Right()];
	cached_map[op_robot_->GetPosition().Up()] = env->GetMap()[scanner_info.position.Up()];
	cached_map[op_robot_->GetPosition().Down()] = env->GetMap()[scanner_info.position.Down()];
	op_robot_->UpdateMap(cached_map);
}
