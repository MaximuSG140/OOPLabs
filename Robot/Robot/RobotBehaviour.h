#pragma once
#include "Behaviour.h"

class RobotBehaviour :
	public Behaviour
{
public:
	RobotBehaviour() = default;
	void Invalidate();
	bool IsCorrect() const;

	virtual void GetSequence();
private:
	bool is_valid_ = true;
};

