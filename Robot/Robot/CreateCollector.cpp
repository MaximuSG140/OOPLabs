#include "CreateCollector.h"

#include "Environment.h"

void CreateCollector::Respond(Environment* env)
{
	env->AddCollector();
}
