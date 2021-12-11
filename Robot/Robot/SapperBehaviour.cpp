#include "SapperBehaviour.h"
#include "Sapper.h"

SapperBehaviour::SapperBehaviour(Sapper* robot) :
	robot_(robot)
{}

Instruction SapperBehaviour::GetInstruction()
{
	if(instructions_.empty())
	{
		GetSequence();
	}
	Instruction res = instructions_.front();
	instructions_.pop();
	return res;
}

void SapperBehaviour::GetSequence()
{
	RobotBehaviour::GetSequence();
	ScaleMap map = robot_->GetMap();
	instructions_ = GetPathToClosest(map.GetBaseMap(),
											map.GetBasePosition(robot_->GetPosition()),
											[](const TileInfo tile) -> bool
											{
												return tile != TileInfo::ROCK &&
													tile != TileInfo::UNKNOWN;
											},
											[](const TileInfo tile) -> bool
											{
												return tile == TileInfo::MINE;
											},
											[](const TileInfo tile) -> tile_action
											{
												if (tile == TileInfo::MINE)return tile_action::step_onto;
												return tile_action::ignore;
											});
}
