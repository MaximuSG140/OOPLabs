#pragma once
#include "EnvironmentQuery.h"
#include "EnvironmentQueryWrapper.h"
#include "Maps.h"

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class Instruction
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	COLLECT_APPLE,
	SCAN,
	AWAIT,
	WAIT
};

class Robot
{
public:
	virtual ~Robot() = default;
	virtual EnvironmentQueryWrapper OnBlow() = 0;
	virtual void Move(Direction move_direction) = 0;
	virtual EnvironmentQueryWrapper PerformAction() = 0;
};

