#include "MapRequest.h"
#include "SmartRobot.h"
#include "UpdateMap.h"

void MapRequest::Receive(SmartRobot* receiver)
{
	receiver->SendMessage(new UpdateMap(receiver->GetMap()));
}
