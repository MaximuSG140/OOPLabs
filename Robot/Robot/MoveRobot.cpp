#include "MoveRobot.h"
#include "Environment.h"
#include "SmartRobot.h"
#include "Maps.h"

MoveRobot::MoveRobot(const Direction move_direction, SmartRobot* moving_robot) :
	operating_robot_(moving_robot),
	move_direction_(move_direction)
{}

void MoveRobot::Perform(Environment* env)
{
	Position new_position{};
	RobotInfo& moving_robot_info = env->GetRobotInfo(operating_robot_);
	switch (move_direction_)
	{
	case Direction::UP:
		new_position = moving_robot_info.position.Up();
		break;
	case Direction::DOWN:
		new_position = moving_robot_info.position.Down();
		break;
	case Direction::LEFT:
		new_position = moving_robot_info.position.Left();
		break;
	case Direction::RIGHT:
		new_position = moving_robot_info.position.Right();
		break;
	}
	SmartRobot* bumped_robot = env->CheckoutPosition(new_position);
	if (bumped_robot != nullptr &&
		bumped_robot->HasAttribute(Attribute::HEAVY))
	{
		return;
	}
	moving_robot_info.position = new_position;
	if(bumped_robot != nullptr)
	{
		bumped_robot->Push(move_direction_).Apply(env);
	}
	if(env->GetMap()[moving_robot_info.position] == TileInfo::ROCK)
	{
		env->RemoveRobot(operating_robot_);
		return;
	}
	if(env->GetMap()[moving_robot_info.position] == TileInfo::MINE)
	{
		operating_robot_->OnBlow().Apply(env);
		env->GetMap().RemoveMine(new_position);
	}
}
