#pragma once
#include "IGameView.h"
#include "SmartRobot.h"
#include "UserCommandWrapper.h"

char InfoToChar(TileInfo info);

class ConsoleView final :
	public IGameView
{
public:
	ConsoleView() = default;
	UserCommandWrapper GetCommand() override;
	Instruction GetInstruction() override;
	void PrintRobotState(SmartRobot& sender) override;
};

