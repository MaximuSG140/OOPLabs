#pragma once
#include "Message.h"

class MapRequest final :
	public Message
{
public:
	void Receive(SmartRobot* receiver) override;
	~MapRequest() override = default;
};

