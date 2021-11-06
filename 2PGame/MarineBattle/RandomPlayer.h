#pragma once
#include "Player.h"

class RandomPlayer final : public Player
{
public:
	Position GetAim() override;
	void EmplaceShips() override;
	void OnShot() override;
private:
	int shotsAmount = 0;
};

