#pragma once

enum class direction{vertical, horizontal};

constexpr int MIN_SHIP_LENGTH = 1;
constexpr int MAX_SHIP_LENGTH = 4;

inline int GetAmmountFromLength(int l)
{
	return MAX_SHIP_LENGTH - l + 1;
}

struct Position
{
	int x = 0;
	int y = 0;
	Position() = default;
	Position(const int x, const int y):
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
	int length;
	int aliveTilesAmount;
	Ship(const Position position, const int length, const enum direction direction):
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

