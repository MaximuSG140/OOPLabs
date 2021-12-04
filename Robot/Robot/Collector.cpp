#include "Collector.h"
#include "CollectResources.h"
#include "ConsoleView.h"
#include "HumanControl.h"
#include "Inspect.h"
#include "MineExploded.h"
#include "MoveRobot.h"
#include "SetSurroundingsInfo.h"
#include "RemoveRobot.h"
#include "RemoveApple.h"
#include "Environment.h"

class BrokenCollector final : public std::exception
{
	Position last_signal_coordinates_;
public:
	explicit BrokenCollector(const Position broke_place) :
		last_signal_coordinates_(broke_place)
	{}
};

Collector::Collector(std::deque<MessageWrapper>& message_sequence) :
	SmartRobot(message_sequence),
	apples_collected_(0)
{}

EnvironmentQueryWrapper Collector::PerformAction()
{
	if (behaviour_ == nullptr)
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
	case Instruction::COLLECT_APPLE:
		Collect();
		return EnvironmentQueryWrapper(new RemoveApple(this));
	case Instruction::SCAN:
		return EnvironmentQueryWrapper(new SetSurroundingsInfo(this));
	case Instruction::AWAIT:
		Deactivate();
		return EnvironmentQueryWrapper();
	case Instruction::WAIT:
		return EnvironmentQueryWrapper();
	}
	throw std::logic_error("Enum value is out of range");
}

EnvironmentQueryWrapper Collector::OnBlow()
{
	SendMessage(new MineExploded(GetPosition()));
	return EnvironmentQueryWrapper(new RemoveRobot(this));
}

void Collector::Collect()
{
	apples_collected_++;
	ScaleMap cached_map = GetMap();
	cached_map[GetPosition()] = TileInfo::EMPTY;
	UpdateMap(cached_map);
}

void Collector::SetInspect(const size_t number)
{
	delete behaviour_;
	behaviour_ = new Inspect(this, number);
	Activate();
}

void Collector::SetCollectResources()
{
	delete behaviour_;
	behaviour_ = new CollectResources(this);
	Activate();
}

void Collector::SetRemote(IGameView* game_interface)
{
	delete behaviour_;
	behaviour_ = new HumanControl(game_interface);
	Activate();
}

std::string Collector::GetRole()
{
	return "Collector";
}

EnvironmentQueryWrapper Collector::Push(const Direction push_direction)
{
	behaviour_->Invalidate();
	return SmartRobot::Push(push_direction);
}

