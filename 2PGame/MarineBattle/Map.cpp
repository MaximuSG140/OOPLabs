#include "Map.h"
#include <iostream>
#include <algorithm>

Map::Map(const map_type relation):
tileInfo(MAP_SIZE, std::vector<tile_state>(MAP_SIZE, relation == map_type::friendly ? tile_state::empty : tile_state::unknown))
{}

Position Map::GetShipHead(Position point) const
{
	while(!IsShipHead(point))
	{
		MoveToHead(point);
	}
	return point;
}

tile_state& Map::operator[](const Position point)
{
	return tileInfo[point.y][point.x];
}

bool IsOffBorders(const Position position)
{
	return position.x < 0 || position.x >= MAP_SIZE || position.y < 0 || position.y >= MAP_SIZE;
}

shot_result Map::ShootAt(const Position aim)
{
	
	if ((*this)[aim] != tile_state::has_ship)
	{
		return shot_result::miss;
	}
	Ship attackedShip = *ships.find({ GetShipHead(aim), 0, direction::vertical });
	ships.erase(attackedShip);
	attackedShip.aliveTilesAmount--;
	tileInfo[aim.y][aim.x] = tile_state::has_attacked_ship;
	if(attackedShip.aliveTilesAmount == 0)
	{
		return shot_result::death;
	}
	ships.insert(attackedShip);
	return shot_result::hit;
}

bool Map::HasEnoughSpace(const Ship newBoat)const
{
	if(newBoat.direction == direction::vertical)
	{
		if(IsOffBorders(newBoat.position) || IsOffBorders({newBoat.position.x, newBoat.position.y + newBoat.length - 1}))
		{
			return false;
		}
		for(int x = std::max(static_cast<int>(newBoat.position.x) - 1, 0); x <= newBoat.position.x + 1; ++x)
		{
			for(int y = std::max(static_cast<int>(newBoat.position.y) - 1, 0); y <= newBoat.position.y + newBoat.length; ++y)
			{
				if(!IsOffBorders({y, x}) && tileInfo[y][x] != tile_state::empty)
				{
					return false;
				}
			}
		}
	}
	else
	{
		if (IsOffBorders(newBoat.position) || IsOffBorders({ newBoat.position.x + newBoat.length - 1 , newBoat.position.y}))
		{
			return false;
		}
		for (int x = std::max(static_cast<int>(newBoat.position.x) - 1, 0); x <= newBoat.position.x + newBoat.length; ++x)
		{
			for (int y = std::max(static_cast<int>(newBoat.position.y) - 1, 0); y <= newBoat.position.y + 1; ++y)
			{
				if (!IsOffBorders({ y, x }))
				{
					if (tileInfo[y][x] != tile_state::empty)
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool Map::PlaceShip(const Ship newBoat)
{
	if(!HasEnoughSpace(newBoat))
	{
		return false;
	}
	ships.insert(newBoat);
	if(newBoat.direction == direction::vertical)
	{
		for(int y = 0; y < newBoat.length; ++y)
		{
			tileInfo[newBoat.position.y + y][newBoat.position.x] = tile_state::has_ship;
		}
	}
	else
	{
		for (int x = 0; x < newBoat.length; ++x)
		{
			tileInfo[newBoat.position.y][newBoat.position.x + x] = tile_state::has_ship;
		}
	}
	return true;
}

bool Map::HasAliveShips() const
{
	return !ships.empty();
}

void Map::MoveToHead(Position& point)const
{
	if (point.y != 0 && tileInfo[point.y - 1][point.x] != tile_state::empty)point.y--;
	if (point.x != 0 && tileInfo[point.y][point.x - 1] != tile_state::empty)point.x--;
}

bool Map::IsShipHead(const Position& point) const
{
	return (point.y == 0 ? true : tileInfo[point.y - 1][point.x] == tile_state::empty)
	&& (point.x == 0 ? true : tileInfo[point.y][point.x - 1] == tile_state::empty);
}
