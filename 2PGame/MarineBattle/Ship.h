#pragma once

enum class direction{vertical, horizontal};

constexpr size_t MIN_SHIP_LENGTH = 1;
constexpr size_t MAX_SHIP_LENGTH = 4;

inline size_t GetAmmountFromLength(size_t l)
{
	return MAX_SHIP_LENGTH - l + 1;
}

struct Position
{
	size_t x = 0;
	size_t y = 0;
	Position() = default;
	Position(const size_t x, const size_t y):
		x(x),
		y(y){}

	bool operator==(const Position& position) const;
	bool operator<(const Position& position) const;

	Position Up() const;
	Position Down() const;
	Position Left() const;
	Position Right() const;
};

inline bool Position::operator==(const Position& position) const
{
	return x == position.x && y == position.y;
}

inline bool Position::operator<(const Position& position) const
{
	return x*x + y*y < position.x*position.x + position.y*position.y;
}

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

struct Ship
{
	Position position;
	direction direction;
	size_t length;
	size_t aliveTilesAmount;
	Ship(const Position position, const size_t length, const enum direction direction):
		position(position),
		direction(direction),
		length(length),
		aliveTilesAmount(length){}
	bool operator<(const Ship& ship)const;
};

inline bool Ship::operator<(const Ship& ship) const
{
	if (position.x == ship.position.x)return position.y < ship.position.y;
	return position.x < ship.position.x;
}

