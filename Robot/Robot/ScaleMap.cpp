#include "ScaleMap.h"
#include <algorithm>

bool ScaleMap::IsOffBorders(const Position point)const
{
	return Map::IsOffBorders(point);
}

Size ScaleMap::FieldSize()const
{
	return Map::FieldSize();
}

ScaleMap::ScaleMap(const Size map_size) :
	Map(map_size, TileInfo::UNKNOWN),
	zeroth_pos_({ 0, 0 })
{}

TileInfo& ScaleMap::operator[](const Position point)
{
	if(!IsOffBorders(point + zeroth_pos_))
	{
		return Map::operator[](point + zeroth_pos_);
	}
	if(point.x + zeroth_pos_.x < 0)
	{
		DoubleLeft();
	}
	if(point.x + zeroth_pos_.x >= static_cast<int>(FieldSize().width))
	{
		DoubleRight();
	}
	if (point.y + zeroth_pos_.y < 0)
	{
		DoubleUp();
	}
	if (point.y + zeroth_pos_.y >= static_cast<int>(FieldSize().height))
	{
		DoubleDown();
	}
	return operator[](point);
}

TileInfo ScaleMap::operator[](const Position point) const
{
	if(IsOffBorders(point + zeroth_pos_))
	{
		return TileInfo::UNKNOWN;
	}
	return Map::operator[](point + zeroth_pos_);
}

int ScaleMap::LeftBorder()const
{
	return -1 * zeroth_pos_.x;
}

int ScaleMap::RightBorder()const
{
	return -1 * zeroth_pos_.x + FieldSize().width;
}

int ScaleMap::UpperBorder()const
{
	return -1 * zeroth_pos_.y;
}

int ScaleMap::BottomBorder()const
{
	return -1 * zeroth_pos_.y + FieldSize().height;
}

Position ScaleMap::GetRandomFreePosition() const
{
	Position pos = { rand() % static_cast<int>(FieldSize().width), rand() % static_cast<int>(FieldSize().height) };
	while(Map::operator[](pos) == TileInfo::UNKNOWN ||
		Map::operator[](pos) == TileInfo::MINE ||
		Map::operator[](pos) == TileInfo::ROCK)
	{
		pos = { rand() % static_cast<int>(FieldSize().width), rand() % static_cast<int>(FieldSize().height) };
	}
	return pos + Position{ LeftBorder(), UpperBorder() };
}

Map ScaleMap::GetBaseMap() const
{
	return static_cast<Map>(*this);
}

Position ScaleMap::GetBasePosition(const Position place) const
{
	return place + zeroth_pos_;
}


void ScaleMap::DoubleLeft()
{
	Map old_map(*this);
	Position old_zeroth_pos = zeroth_pos_;
	*this = ScaleMap({ old_map.FieldSize().width * 2, old_map.FieldSize().height });
	zeroth_pos_ = old_zeroth_pos;
	zeroth_pos_.x += old_map.FieldSize().width;
	for(int i = 0; i < old_map.FieldSize().width; ++i)
	{
		for(int j = 0; j < old_map.FieldSize().height; j++)
		{
			Map::operator[]({ static_cast<int>(old_map.FieldSize().width) + i ,j }) = old_map[{i, j}];
		}
	}
}

void ScaleMap::DoubleRight()
{
	Map old_map(*this);
	Position olt_zeroth_pos = zeroth_pos_;
	*this = ScaleMap({ old_map.FieldSize().width * 2, old_map.FieldSize().height });
	zeroth_pos_ = olt_zeroth_pos;
	for (int i = 0; i < old_map.FieldSize().width; ++i)
	{
		for (int j = 0; j < old_map.FieldSize().height; j++)
		{
			Map::operator[]({i, j}) = old_map[{i, j}];
		}
	}
}

void ScaleMap::DoubleUp()
{
	Map old_map(*this);
	Position old_zeroth_pos = zeroth_pos_;
	*this = ScaleMap({ old_map.FieldSize().width, old_map.FieldSize().height * 2});
	zeroth_pos_ = old_zeroth_pos;
	zeroth_pos_.y += old_map.FieldSize().height;
	for (int i = 0; i < old_map.FieldSize().width; ++i)
	{
		for (int j = 0; j < old_map.FieldSize().height; j++)
		{
			Map::operator[]({ i, static_cast<int>(old_map.FieldSize().height) + j}) = old_map[{i, j}];
		}
	}
}

void ScaleMap::DoubleDown()
{
	Map old_map(*this);
	Position old_zeroth_pos = zeroth_pos_;
	*this = ScaleMap({ old_map.FieldSize().width, old_map.FieldSize().height * 2 });
	zeroth_pos_ = old_zeroth_pos;
	for (int i = 0; i < old_map.FieldSize().width; ++i)
	{
		for (int j = 0; j < old_map.FieldSize().height; j++)
		{
			Map::operator[]({i, j}) = old_map[{i, j}];
		}
	}
}

void ScaleMap::Update(const ScaleMap& other)
{
	for(int y = std::min(UpperBorder(), other.UpperBorder()); y < std::max(BottomBorder(), other.BottomBorder()); ++y)
	{
		for (int x = std::min(LeftBorder(), other.LeftBorder()); x < std::max(RightBorder(), other.RightBorder()); ++x)
		{
			if (operator[]({ x, y }) == TileInfo::UNKNOWN)operator[]({ x, y }) = other[{ x, y }];
			if (other[{ x, y }] == TileInfo::UNKNOWN)operator[]({ x, y }) = operator[]({x, y});
			if (operator[]({ x, y }) == TileInfo::EMPTY)operator[]({ x, y }) = TileInfo::EMPTY;
			if (other[{ x, y }] == TileInfo::EMPTY)operator[]({ x, y }) = TileInfo::EMPTY;
		}
	}
}
