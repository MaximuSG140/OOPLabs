#pragma once
#include "SmartRobot.h"

class UserCommand
{
public:
	virtual ~UserCommand() = default;
	virtual void Respond(Environment* env)=0;
};

