#include "EffectivePlayer.h"
#include <algorithm>
#include <iostream>

Position EffectivePlayer::GetAim()
{
	if(prioritizedAims.empty())
	{
		Position aim = { 0, 0 };
		while(!IsOffBorders(aim) && enemyField[aim] != tile_state::unknown)
		{
			if(aim.x < MAP_SIZE - 1)
			{
				aim.x++;
			}
			else
			{
				aim.y++;
				aim.x = 0;
			}
		}
		std::cout << aim.x << ' ' << aim.y << std::endl;
		return aim;
	}
	Position aim = { 0, 0 };
	while(!prioritizedAims.empty() && enemyField[aim] != tile_state::unknown)
	{
		aim = prioritizedAims.front();
		prioritizedAims.pop();
	}
	if(enemyField[aim] == tile_state::unknown)
	{
		std::cout << aim.x << ' ' << aim.y << std::endl;
		return aim;
	}
	return GetAim();
}

void EffectivePlayer::EmplaceShips()
{
	friendlyField = Map(map_type::friendly);
	enemyField = Map(map_type::hostile);
	for (size_t length = MIN_SHIP_LENGTH; length <= MAX_SHIP_LENGTH; ++length)
	{
		for (size_t i = 0; i < GetAmmountFromLength(length); ++i)
		{
			Position toPlace(rand() % MAP_SIZE, rand() % MAP_SIZE);
			direction dir = rand() % 2 ? direction::horizontal : direction::vertical;
			while (!friendlyField.PlaceShip({ toPlace, length, dir }))
			{
				toPlace = { rand() % MAP_SIZE, rand() % MAP_SIZE };
				dir = rand() % 2 ? direction::horizontal : direction::vertical;
			}
		}
	}
}

void EffectivePlayer::OnMiss(const Position position)
{
	Player::OnMiss(position);
}

void EffectivePlayer::OnHit(const Position position)
{
	Player::OnHit(position);
	auto SetEmpty = [&](const Position point)->void
	{
		if (!IsOffBorders(point))
		{
			enemyField[point] = tile_state::empty;
		}
	};
	SetEmpty(position.Left().Up());
	SetEmpty(position.Left().Down());
	SetEmpty(position.Right().Up());
	SetEmpty(position.Right().Down());

	auto MakePrioritized = [&](const Position point)->void
	{
		if (!IsOffBorders(point) && enemyField[point] == tile_state::unknown)
		{
			prioritizedAims.push(point);
		}
	};
	MakePrioritized(position.Right());
	MakePrioritized(position.Left());
	MakePrioritized(position.Up());
	MakePrioritized(position.Down());
}

void EffectivePlayer::OnKill(const Position position)
{
	Player::OnKill(position);
	Position deadShipHead = enemyField.GetShipHead(position);
	if (!IsOffBorders(deadShipHead.Down()) 
		&& enemyField[deadShipHead.Down()] == tile_state::has_attacked_ship)
	{
		auto DefineStrip = [&](size_t y) -> void
		{
			for (size_t x = std::max(static_cast<int>(deadShipHead.x) - 1, 0); x <= deadShipHead.x + 1; ++x)
			{
				if (!IsOffBorders({ x, y }) && (enemyField[{x, y}] != tile_state::has_attacked_ship))
				{
					enemyField[{x, y}] = tile_state::empty;
				}
			}
		};
		size_t y = std::max(static_cast<int>(deadShipHead.y) - 1, 0);
		
		DefineStrip(y);
		y++;
		while(!IsOffBorders({ deadShipHead.x, y }) && enemyField[{ deadShipHead.x, y }] == tile_state::has_attacked_ship)
		{
			DefineStrip(y);
			y++;
		}
		DefineStrip(y);
	}
	else
	{
		auto DefineStrip = [&](size_t x) -> void
		{
			for (size_t y = std::max(static_cast<int>(deadShipHead.y) - 1, 0); y <= deadShipHead.y + 1; ++y)
			{
				if (!IsOffBorders({ x, y }) && !(enemyField[{x, y}] == tile_state::has_attacked_ship))
				{
					enemyField[{x, y}] = tile_state::empty;
				}
			}
		};
		size_t x = std::max(static_cast<int>(deadShipHead.x) - 1, 0);

		DefineStrip(x);
		x++;
		while (!IsOffBorders({ x, deadShipHead.y }) && enemyField[{ x, deadShipHead.y }] == tile_state::has_attacked_ship)
		{
			DefineStrip(x);
			x++;
		}
		DefineStrip(x);
	}
}
