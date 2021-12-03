#pragma once
#include <vector>

enum class TileInfo
{
	UNKNOWN,
	EMPTY,
	MINE,
	APPLE,
	ROCK
};

struct Size
{
	size_t width;
	size_t height;
};

struct Position
{
	int x;
	int y;

	Position Up() const;
	Position Down() const;
	Position Left() const;
	Position Right() const;
	bool operator==(const Position& other) const;
	Position operator+(const Position& second)const;
	Position operator-(const Position& second)const;
};

inline Position Position::Up() const
{
	return { x, y - 1 };
}

inline Position Position::Down() const
{
	return { x, y + 1 };
}

inline Position Position::Left() const
{
	return { x - 1, y };
}

inline Position Position::Right() const
{
	return { x + 1, y };
}


class Map
{
public:
	Map() = default;
	Map(Size map_size, TileInfo base_tile_val);

	bool IsOffBorders(Position point)const;
	Size FieldSize()const;
	std::vector<TileInfo>& operator[](size_t index);
	TileInfo& operator[](Position point);
	TileInfo operator[](Position point)const;
private:
	std::vector<std::vector<TileInfo> > tiles_;
};

