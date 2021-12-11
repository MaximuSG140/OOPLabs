#include "ChangeRobotBehaviour.h"

#include "Collector.h"
#include "Environment.h"

ChangeCollectorBehaviour::ChangeCollectorBehaviour(SmartRobot* id, const RobotBehaviourModel behaviour, std::vector<std::string> args):
	robot_id_(id),
	new_behaviour_(behaviour),
	args_(std::move(args))
{}

void ChangeCollectorBehaviour::Respond(Environment* env)
{
	RobotInfo& info = env->GetRobotInfo(robot_id_);
	auto collector = dynamic_cast<Collector*>(info.robot);
	if(collector == nullptr)
	{
		throw std::logic_error("This robot can't use this behaviour!");
	}
	switch(new_behaviour_)
	{
	case RobotBehaviourModel::COLLECT:
		if(!args_.empty())
		{
			throw std::logic_error("Wrong argument amount!");
		}
		collector->SetCollectResources();
		break;
	case RobotBehaviourModel::SCOUT:
		if(args_.size() != 1)
		{
			throw std::logic_error("Wrong argument amount!");
		}
		collector->SetInspect(atoi(args_[0].c_str()));
		break;
	case RobotBehaviourModel::TRIGGER_MINES:
		throw std::logic_error("This robot can't use this behaviour!");
	case RobotBehaviourModel::MANUAL:
		collector->SetRemote(env->GetView());
		break;
	}
}
