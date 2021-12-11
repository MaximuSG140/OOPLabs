#pragma once
#include "IGameView.h"
#include "RobotBehaviour.h"

class HumanControl final :
	public RobotBehaviour
{
public:
	explicit HumanControl(IGameView* game_view);
	Instruction GetInstruction()override;
private:
	IGameView* game_interface_;
};

