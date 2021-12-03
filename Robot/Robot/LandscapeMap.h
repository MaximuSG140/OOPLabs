#pragma once
#include <string>
#include "Map.h"

class LandscapeMap final :
	protected Map
{
public:
	explicit LandscapeMap(const std::string& file_name);

	TileInfo operator[](Position point)const;

	Size FieldSize()const;

	bool RemoveApple(Position point);
	bool RemoveMine(Position point);
};
