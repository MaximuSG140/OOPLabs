#pragma once
#include "UserCommand.h"

class CreateSapper final :
	public UserCommand
{
public:
	explicit CreateSapper(SmartRobot* master);
	void Respond(Environment* env) override;
private:
	SmartRobot* master_;
};

