#include "LandscapeMap.h"
#include "fstream"

TileInfo CharToInfo(const char value)
{
	switch (value)
	{
	case '^':return TileInfo::ROCK;
	case '0':return TileInfo::APPLE;
	case ' ':return TileInfo::EMPTY;
	case '*':return TileInfo::MINE;
	default: return TileInfo::EMPTY;
	}
}

Size GetMapSize(const std::string& file_name)
{
	std::ifstream lines(file_name);
	std::string current_line;
	size_t height = 0;
	while(std::getline(lines, current_line))
	{
		height++;
	}
	size_t width = current_line.size();
	return { width, height };
}

LandscapeMap::LandscapeMap(const std::string& file_name) :
	Map(GetMapSize(file_name), TileInfo::EMPTY)
{
	std::string current_line;
	std::ifstream lines(file_name);
	size_t current = 0;
	while(std::getline(lines, current_line))
	{
		for (int i = 0; i < current_line.size(); ++i)
		{
			Map::operator[](current)[i] = CharToInfo(current_line[i]);
		}
		current++;
	}
}

TileInfo LandscapeMap::operator[](const Position point) const
{
	if (point.x < 0 ||
		point.y < 0 ||
		point.x >= FieldSize().width ||
		point.y >= FieldSize().height)
	{
		return TileInfo::ROCK;
	}
	return Map::operator[](point);
}

Size LandscapeMap::FieldSize()const
{
	return Map::FieldSize();
}

bool LandscapeMap::RemoveApple(const Position point)
{
	if ((*this)[point] != TileInfo::APPLE)return false;
	Map::operator[](point) = TileInfo::EMPTY;
	return true;
}

bool LandscapeMap::RemoveMine(const Position point)
{
	if ((*this)[point] != TileInfo::MINE)return false;
	Map::operator[](point) = TileInfo::EMPTY;
	return true;
}
