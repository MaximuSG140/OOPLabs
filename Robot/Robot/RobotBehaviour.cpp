#include "RobotBehaviour.h"

void RobotBehaviour::Invalidate()
{
	is_valid_ = false;
}

bool RobotBehaviour::IsCorrect() const
{
	return is_valid_;
}

void RobotBehaviour::GetSequence()
{
	is_valid_ = true;
}

