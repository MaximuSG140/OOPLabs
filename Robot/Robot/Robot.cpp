#include "Robot.h"
#include <chrono>

Robot::Robot(LandscapeMap& marsSurface) :
	realMap(marsSurface)
{
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	position = { rand() % realMap.FieldSize().width, rand() % realMap.FieldSize().height };
}

LandscapeMap& Robot::GetRealMap() const
{
	return realMap;
}

bool Robot::IsAbleToMove(const Position& point)
{
	return realMap[point] != tile_info::rock;
}

void Robot::OnMoveUp(){}

void Robot::OnMoveDown(){}

void Robot::OnMoveLeft(){}

void Robot::OnMoveRight(){}

void Robot::OnAppleCollecting()
{
	realMap.RemoveApple(position);
}

void Robot::OnBlow()
{
	realMap.RemoveMine(position);
}

tile_info Robot::Scan(const Position& point) const
{
	return realMap[point];
}

void Robot::OnForceMove()
{}

void Robot::OnHit(){}

void Robot::Move(const direction vector)
{
	switch(vector)
	{
	case direction::up:
		if (!IsAbleToMove(position.Up()))
		{
			return;
		}
		OnMoveUp();
		position = position.Up();
		break;
	case direction::down:
		if (!IsAbleToMove(position.Down()))
		{
			return;
		}
		OnMoveDown();
		position = position.Down();
		break;
	case direction::left:
		if (!IsAbleToMove(position.Left()))
		{
			return;
		}
		OnMoveLeft();
		position = position.Left();
		break;
	case direction::right:
		if (!IsAbleToMove(position.Right()))
		{
			return;
		}
		OnMoveRight();
		position = position.Right();
		break;
	}
	if (realMap[position] == tile_info::mine)
	{
		OnBlow();
	}
}

tile_info Robot::GetGroundInfo() const
{
	return realMap[position];
}

Position Robot::GetPosition()const
{
	return position;
}

void Robot::ForceMove(const direction vector)
{
	switch (vector)
	{
	case direction::up:
		OnMoveUp();
		position = position.Up();
		break;
	case direction::down:
		OnMoveDown();
		position = position.Down();
		break;
	case direction::left:
		OnMoveLeft();
		position = position.Left();
		break;
	case direction::right:
		OnMoveRight();
		position = position.Right();
		break;
	}
	OnForceMove();
	if (realMap[position] == tile_info::mine)
	{
		OnBlow();
	}
	if (realMap[position] == tile_info::rock)
	{
		OnHit();
	}
}
