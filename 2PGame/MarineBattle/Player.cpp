#include "Player.h"
#include <iostream>

void Player::Attack(Player& opponent)
{
	Position aim = GetAim();
	switch(opponent.friendlyField.ShootAt(aim))
	{
	case shot_result::miss:
		OnMiss(aim);
		break;
	case shot_result::hit:
		OnHit(aim);
		break;
	case shot_result::death:
		OnKill(aim);
		break;
	}
	OnShot();
}

char GetTileIcon(const tile_state state)
{
	switch(state)
	{
	case tile_state::unknown: return '?';
	case tile_state::empty: return ' ';
	case tile_state::has_ship: return '#';
	case tile_state::has_attacked_ship: return '*';
	}
}

void PrintField(const std::vector<std::vector<tile_state> >& field)
{
	std::cout << " |0|1|2|3|4|5|6|7|8|9|" << std::endl;
	std::cout << "----------------------" << std::endl;
	for(int i = 0; i < MAP_SIZE; ++i)
	{
		std::cout << i << "|";
		for(int j = 0; j < MAP_SIZE; ++j)
		{
			std::cout << GetTileIcon(field[i][j]) << "|";
		}
		std::cout << std::endl;
		std::cout << "----------------------" << std::endl;
	}
}

void Player::PrintFields() const
{
	auto my = friendlyField.GetSnapshot();
	auto opponent = enemyField.GetSnapshot();
	std::cout << "My field:" << std::endl;
	PrintField(my);
	std::cout << "Enemy field" << std::endl;
	PrintField(opponent);
}

bool Player::HasAliveShips() const
{
	return friendlyField.HasAliveShips();
}

void Player::OnMiss(const Position aim)
{
	std::cout << "Miss!" << std::endl;
	enemyField[aim] = tile_state::empty;
}

void Player::OnHit(const Position aim)
{
	std::cout << "Hit!" << std::endl;
	enemyField[aim] = tile_state::has_attacked_ship;
}

void Player::OnKill(const Position aim)
{
	std::cout << "Kill!" << std::endl;
	enemyField[aim] = tile_state::has_attacked_ship;
}
