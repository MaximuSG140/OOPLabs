#pragma once
#include <vector>
#include <set>
#include "Ship.h"

enum class map_type{friendly, hostile};

enum class tile_state{unknown = 0, empty, has_ship, has_attacked_ship};

enum class shot_result{miss, hit, death};

constexpr size_t MAP_SIZE = 10;

bool IsOffBorders(const Position position);

class Map
{
public:
	explicit Map(map_type);

	Position GetShipHead(Position)const;

	tile_state& operator[](Position);

	auto GetSnapshot() const
	{
		return tileInfo;
	}
	shot_result ShootAt(Position);
	bool HasEnoughSpace(Ship)const;
	bool PlaceShip(Ship);
	bool HasAliveShips()const;
private:
	std::vector<std::vector<tile_state> > tileInfo;
	std::set<Ship> ships;

	void MoveToHead(Position&)const;
	bool IsShipHead(const Position&)const;
};

