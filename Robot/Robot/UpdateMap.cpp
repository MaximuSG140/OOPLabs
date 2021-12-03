#include "UpdateMap.h"

#include <utility>

#include "SmartRobot.h"

UpdateMap::UpdateMap(ScaleMap map) :
	sent_map_(std::move(map))
{}

void UpdateMap::Receive(SmartRobot* receiver)
{
	receiver->UpdateMap(sent_map_);
	receiver->Activate();
}
