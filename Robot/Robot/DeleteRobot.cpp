#include "DeleteRobot.h"
#include "Environment.h"

DeleteRobot::DeleteRobot(SmartRobot* delete_id) :
	delete_id_(delete_id)
{}

void DeleteRobot::Respond(Environment* env)
{
	env->RemoveRobot(delete_id_);
}
