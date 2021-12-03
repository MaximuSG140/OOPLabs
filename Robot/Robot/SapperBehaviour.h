#pragma once
#include "RobotBehaviour.h"
#include "FindClosest.h"

class Sapper;

class SapperBehaviour final :
	public RobotBehaviour
{
public:
	explicit SapperBehaviour(Sapper* robot);
	Instruction GetInstruction()override;
	void GetSequence()override;
private:
	std::queue<Instruction> instructions_;
	Sapper* robot_;
};

