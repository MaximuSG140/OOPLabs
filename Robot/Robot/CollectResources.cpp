#include "CollectResources.h"
#include "Collector.h"

CollectResources::CollectResources(Collector* robot) :
	robot_(robot)
{}

void CollectResources::GetSequence()
{
	RobotBehaviour::GetSequence();
	ScaleMap map = robot_->GetMap();
	instructions_ = GetPathToClosest(map.GetBaseMap(),
											map.GetBasePosition(robot_->GetPosition()), 
											[](const TileInfo tile)->bool
											{
												return tile != TileInfo::ROCK &&
													tile != TileInfo::UNKNOWN &&
													tile != TileInfo::MINE;
											},
											[](const TileInfo tile) -> bool
											{
												return tile == TileInfo::APPLE;
											},
											[](const TileInfo tile) -> tile_action
											{
												if (tile == TileInfo::APPLE)return tile_action::collect;
												return tile_action::ignore;
											});
}

Instruction CollectResources::GetInstruction()
{
	if(instructions_.empty() || !IsCorrect())
	{
		GetSequence();
	}
	Instruction res = instructions_.front();
	instructions_.pop();
	return res;
}
