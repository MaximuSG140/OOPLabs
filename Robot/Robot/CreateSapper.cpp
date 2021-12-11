#include "CreateSapper.h"
#include "Environment.h"

CreateSapper::CreateSapper(SmartRobot* master) :
	master_(master)
{}

void CreateSapper::Respond(Environment* env)
{
	env->AddSapper(master_);
}
