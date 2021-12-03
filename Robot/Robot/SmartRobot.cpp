#include "SmartRobot.h"
#include "Environment.h"
#include "Message.h"
#include "MoveRobot.h"

constexpr int MINIMAL_MAP_SIZE = 3;

class RobotIsDestroyed final :
	public std::exception
{};

SmartRobot::SmartRobot(std::deque<MessageWrapper>& radio_messages, std::set<Attribute> attributes) :
	radio_(radio_messages),
	place_({MINIMAL_MAP_SIZE/2, MINIMAL_MAP_SIZE/2}),
	map_({MINIMAL_MAP_SIZE, MINIMAL_MAP_SIZE}),
	attributes_(std::move(attributes)),
	master_(this),
	is_active_(true)
{}

SmartRobot::SmartRobot(std::deque<MessageWrapper>& radio_messages,
		const SmartRobot* master,
		const Position place,
		std::set<Attribute> attributes) :
	SmartRobot(radio_messages, std::move(attributes))
{
	this->master_ = master;
	this->place_ = place;
}

void SmartRobot::UpdateMap(const ScaleMap& updated_map)
{
	map_.Update(updated_map);
}

void SmartRobot::SendMessage(Message* msg)
{
	radio_.emplace_back(this, msg);
}

void SmartRobot::ReceiveMessage(const MessageWrapper& msg)
{
	if(msg.Sender()->master_ == master_ &&
		msg.Sender() != this)
	{
		msg.Msg()->Receive(this);
	}
}

void SmartRobot::Activate()
{
	is_active_ = true;
}

void SmartRobot::Deactivate()
{
	is_active_ = false;
}

EnvironmentQueryWrapper SmartRobot::Push(const Direction push_direction)
{
	Move(push_direction);
	return EnvironmentQueryWrapper(new MoveRobot(push_direction, this));
}

bool SmartRobot::IsActive() const
{
	return is_active_;
}

bool SmartRobot::HasAttribute(const Attribute a) const
{
	return attributes_.count(a) == 1;
}

Position SmartRobot::GetPosition() const
{
	return place_;
}

ScaleMap SmartRobot::GetMap() const
{
	return map_;
}

const SmartRobot* SmartRobot::GetMasterId() const
{
	return master_;
}

void SmartRobot::Move(const Direction move_direction)
{
	switch(move_direction)
	{
	case Direction::UP:
		place_ = place_.Up();
		break;
	case Direction::DOWN:
		place_ = place_.Down();
		break;
	case Direction::LEFT:
		place_ = place_.Left();
		break;
	case Direction::RIGHT:
		place_ = place_.Right();
		break;
	}
}

