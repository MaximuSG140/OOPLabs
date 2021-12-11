#pragma once
#include "Robot.h"

enum class RobotBehaviourModel{COLLECT, SCOUT, TRIGGER_MINES, MANUAL };

class Behaviour
{
public:
	virtual Instruction GetInstruction()=0;
	virtual ~Behaviour() = default;
};

