#pragma once
#include "Player.h"
class ConsolePlayer final : public Player
{
	Position GetAim() override;
	void EmplaceShips() override;
};

