#include "Inspect.h"


Inspect::Inspect(Collector* robot, const size_t steps_amount) :
	steps_ammount_(steps_amount),
	robot_(robot)
{}

void Inspect::GetSequence()
{
	RobotBehaviour::GetSequence();
	ScaleMap map = robot_->GetMap();
	instructions_ = GetPathToClosest(map.GetBaseMap(),
											map.GetBasePosition(robot_->GetPosition()),
											[](const TileInfo tile)->bool
											{
												return tile != TileInfo::MINE &&
													tile != TileInfo::ROCK &&
													tile != TileInfo::UNKNOWN;
											},
											[](const TileInfo tile) -> bool
											{
												return tile == TileInfo::UNKNOWN;
											},
											[](const TileInfo tile) -> tile_action
											{
												if (tile == TileInfo::UNKNOWN)return tile_action::scan;
												return tile_action::ignore;
											});
}

Instruction Inspect::GetInstruction()
{
	if(steps_ammount_ == 0)
	{
		return Instruction::AWAIT;
	}
	if(!IsCorrect() || instructions_.empty())
	{
		GetSequence();
	}
	Instruction single_instruction = instructions_.front();
	instructions_.pop();
	steps_ammount_--;
	return single_instruction;
}
