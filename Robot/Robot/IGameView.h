#pragma once
#include "SmartRobot.h"
#include "UserCommandWrapper.h"

class Collector;

class IGameView
{
public:
	virtual UserCommandWrapper GetCommand()=0;
	virtual Instruction GetInstruction()=0;
	virtual ~IGameView()=default;
	virtual void PrintRobotState(SmartRobot& sender)=0;
};

