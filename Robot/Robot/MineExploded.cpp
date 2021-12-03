#include "Environment.h"
#include "SmartRobot.h"
#include "ScaleMap.h"
#include "MineExploded.h"

MineExploded::MineExploded(const Position explosion_place) :
	place_(explosion_place)
{}

void MineExploded::Receive(SmartRobot* receiver)
{
	ScaleMap cached_map = receiver->GetMap();
	cached_map[place_] = TileInfo::EMPTY;
	receiver->UpdateMap(cached_map);
	receiver->Activate();
}
