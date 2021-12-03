#pragma once
#include "UserCommand.h"

class DeleteRobot final :
	public UserCommand
{
public:
	explicit DeleteRobot(SmartRobot* delete_id);
	void Respond(Environment* env) override;
private:
	SmartRobot* delete_id_;
};

