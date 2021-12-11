#pragma once
#include "Message.h"
#include "ScaleMap.h"

class UpdateMap final :
	public Message
{
public:
	explicit UpdateMap(ScaleMap map);
	void Receive(SmartRobot* receiver) override;
	~UpdateMap() override = default;
private:
	ScaleMap sent_map_;
};

