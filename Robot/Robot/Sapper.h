#pragma once
#include "SmartRobot.h"
#include "RobotBehaviour.h"
#include <deque>

class Sapper final :
	public SmartRobot
{
public:
	explicit Sapper(std::deque<MessageWrapper>& radio_messages, const SmartRobot* master, Position place);

	EnvironmentQueryWrapper PerformAction() override;
	EnvironmentQueryWrapper Push(Direction push_direction) override;
	std::string GetRole() override;
	EnvironmentQueryWrapper OnBlow() override;
private:
	RobotBehaviour* behaviour_;
};

