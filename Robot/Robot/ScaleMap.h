#pragma once
#include "Map.h"
class ScaleMap :
	protected Map
{
public:
	bool IsOffBorders(Position point)const;
	Size FieldSize()const;
	explicit ScaleMap(Size map_size);
	TileInfo& operator[](Position point);
	TileInfo operator[](Position point)const;

	int LeftBorder()const;
	int RightBorder()const;
	int UpperBorder()const;
	int BottomBorder()const;

	Position GetRandomFreePosition()const;

	Map GetBaseMap()const;
	Position GetBasePosition(Position place)const;

	void DoubleLeft();
	void DoubleRight();
	void DoubleUp();
	void DoubleDown();
	void Update(const ScaleMap& other);
private:
	Position zeroth_pos_;
};

