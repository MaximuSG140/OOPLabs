#pragma once
#include <queue>
#include "Player.h"

class EffectivePlayer final :
    public Player
{
public:
    Position GetAim() override;
    void EmplaceShips() override;
    void OnMiss(Position) override;
    void OnHit(Position) override;
    void OnKill(Position) override;
private:
    int clearTiles = 0;
    std::queue<Position> prioritizedAims;
};

