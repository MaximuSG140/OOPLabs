#pragma once
#include "RobotBehaviour.h"
#include "FindClosest.h"

class Collector;

class CollectResources final :
	public RobotBehaviour
{
public:
	explicit CollectResources(Collector* robot);
	void GetSequence() override;
	Instruction GetInstruction() override;
private:
	Collector* robot_;
	std::queue<Instruction> instructions_;
};

