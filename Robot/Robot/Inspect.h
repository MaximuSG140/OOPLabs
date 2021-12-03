#pragma once
#include "Collector.h"
#include "RobotBehaviour.h"
#include "FindClosest.h"

class Inspect final :
	public RobotBehaviour
{
public:
	Inspect(Collector* robot, size_t steps_amount);
	void GetSequence()override;
	Instruction GetInstruction()override;
private:
	size_t steps_ammount_;
	std::queue<Instruction> instructions_;
	Collector* robot_;
};

