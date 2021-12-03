#include "Sapper.h"
#include "MineExploded.h"
#include "MoveRobot.h"
#include "MapRequest.h"
#include "SapperBehaviour.h"

class InconsistentOrder final : std::exception
{};

Sapper::Sapper(std::deque<MessageWrapper>& radio_messages, SmartRobot* master, const Position place) :
	SmartRobot(radio_messages, master, place, {Attribute::HEAVY, Attribute::UNBREAKABLE}),
	behaviour_(new SapperBehaviour(this))
{}

EnvironmentQueryWrapper Sapper::PerformAction()
{
	if(behaviour_ == nullptr)
	{
		Deactivate();
		return EnvironmentQueryWrapper();
	}
	switch (behaviour_->GetInstruction())
	{
	case Instruction::MOVE_UP:
		Move(Direction::UP);
		return EnvironmentQueryWrapper(new MoveRobot(Direction::UP, this));
	case Instruction::MOVE_DOWN:
		Move(Direction::DOWN);
		return EnvironmentQueryWrapper(new MoveRobot(Direction::DOWN, this));
	case Instruction::MOVE_LEFT:
		Move(Direction::LEFT);
		return EnvironmentQueryWrapper(new MoveRobot(Direction::LEFT, this));
	case Instruction::MOVE_RIGHT:
		Move(Direction::RIGHT);
		return EnvironmentQueryWrapper(new MoveRobot(Direction::RIGHT, this));
	case Instruction::AWAIT:
		SendMessage(new MapRequest());
		Deactivate();
		return EnvironmentQueryWrapper();
	default:
		throw InconsistentOrder();
	}
}

EnvironmentQueryWrapper Sapper::Push(const Direction push_direction)
{
	behaviour_->Invalidate();
	return SmartRobot::Push(push_direction);
}

std::string Sapper::GetRole()
{
	return "Sapper";
}

EnvironmentQueryWrapper Sapper::OnBlow()
{
	ScaleMap new_map = GetMap();
	new_map[GetPosition()] = TileInfo::EMPTY;
	UpdateMap(new_map);
	SendMessage(new MineExploded(GetPosition()));
	return EnvironmentQueryWrapper();
}
