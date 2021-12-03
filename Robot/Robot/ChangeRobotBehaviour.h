#pragma once
#include "Behaviour.h"
#include "UserCommand.h"

class ChangeCollectorBehaviour final :
	public UserCommand
{
public:
	ChangeCollectorBehaviour(SmartRobot*, RobotBehaviourModel, std::vector<std::string>);
	void Respond(Environment*) override;
private:
	SmartRobot* robot_id_;
	RobotBehaviourModel new_behaviour_;
	std::vector<std::string> args_;
};

