#pragma once
#include "Map.h"

class Player
{
public:
	void Attack(Player&);
	void PrintFields() const;
	virtual Position GetAim() = 0;
	bool HasAliveShips() const;
	virtual void EmplaceShips() = 0;

	virtual void OnShot();
	virtual void OnMiss(Position);
	virtual void OnHit(Position);
	virtual void OnKill(Position);

	virtual ~Player() = default;
protected:
	Map friendlyField = Map(map_type::friendly);
	Map enemyField = Map(map_type::hostile);
};

inline void Player::OnShot(){}

