#include "Map.h"

bool Position::operator==(const Position& other) const
{
	return x == other.x && y == other.y;
}

Position Position::operator+(const Position& second) const
{
	return{ x + second.x, y + second.y };
}

Position Position::operator-(const Position& second) const
{
	return { x - second.x, y - second.y };
}

Map::Map(const Size map_size, const TileInfo base_tile_val) :
	tiles_(map_size.height, std::vector<TileInfo>(map_size.width, base_tile_val))
{}

bool Map::IsOffBorders(const Position point)const
{
	return point.y >= tiles_.size() || point.x >= tiles_[0].size();
}

Size Map::FieldSize() const
{
	return { tiles_[0].size(), tiles_.size() };
}

std::vector<TileInfo>& Map::operator[](const size_t index)
{
	return tiles_[index];
}

TileInfo& Map::operator[](const Position point)
{
	return tiles_[point.y][point.x];
}

TileInfo Map::operator[](const Position point) const
{
	return tiles_[point.y][point.x];
}
