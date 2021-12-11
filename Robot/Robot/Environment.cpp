#include "Environment.h"
#include "SmartRobot.h"
#include "Sapper.h"
#include "Collector.h"
#include "EnvironmentQueryWrapper.h"
#include "IGameView.h"
#include "LandscapeMap.h"
#include "UserCommandWrapper.h"

Environment::Environment(IGameView* game_view, const std::string& file_name) :
	real_map_(file_name),
	view_(game_view)
{}

RobotInfo& Environment::GetRobotInfo(SmartRobot* search_id)
{
	for (auto& info : robot_infos_)
	{
		if(info.robot == search_id)
		{
			return info;
		}
	}
	throw std::logic_error("No such robot available");
}

LandscapeMap& Environment::GetMap()
{
	return real_map_;
}

void Environment::RemoveRobot(SmartRobot* remove_id)
{
	RobotInfo& info = GetRobotInfo(remove_id);
	info.robot = nullptr;
	robot_infos_.erase(
		std::remove_if(
			robot_infos_.begin(),
			robot_infos_.end(),
			[](const RobotInfo checking_info) -> bool
			{
				return checking_info.robot == nullptr;
			}),
		robot_infos_.end());
	current_radio_messages_.erase(
		std::remove_if(
			current_radio_messages_.begin(), 
			current_radio_messages_.end(), 
			[&](const MessageWrapper& message) -> bool
			{
				return message.Sender() == remove_id;
			}),
		current_radio_messages_.end());
	previous_radio_messages_.erase(
		std::remove_if(
			previous_radio_messages_.begin(),
			previous_radio_messages_.end(),
			[&](const MessageWrapper& message) -> bool
			{
				return message.Sender() == remove_id;
			}),
		previous_radio_messages_.end());
	delete remove_id;
}

void Environment::AskForNewOptions()
{
	UserCommandWrapper command_wrapper = view_->GetCommand();
	while(command_wrapper)
	{
		command_wrapper.Perform(this);
		command_wrapper = view_->GetCommand();
	}
}

void Environment::MakeTurn()
{
	bool has_active_robots = false;
	for (auto& info : robot_infos_)
	{
		if(info.robot == nullptr)
		{
			continue;
		}
		for (auto& message : previous_radio_messages_)
		{
			info.robot->ReceiveMessage(message);
		}

		if (info.robot->IsActive())
		{
			has_active_robots = true;
			(info.robot->PerformAction()).Apply(this);
		}
		view_->PrintRobotState(*info.robot);
	}
	if(!has_active_robots)
	{
		AskForNewOptions();
	}
	previous_radio_messages_ = std::move(current_radio_messages_);
	current_radio_messages_ = std::deque<MessageWrapper>();
}

void Environment::AddCollector()
{
	robot_infos_.push_back(
		{
			{
				static_cast<int>(rand() % real_map_.FieldSize().width),
				static_cast<int>(rand() % real_map_.FieldSize().height)
			},
			new Collector(current_radio_messages_)
		});
}

void Environment::AddSapper(SmartRobot* master)
{
	Position sapper_coordinates = master->GetMap().GetRandomFreePosition();
	robot_infos_.push_back(
		{
			GetRobotInfo(master).position + sapper_coordinates - master->GetPosition(),
			new Sapper(current_radio_messages_, master, sapper_coordinates)
		});
}

SmartRobot* Environment::CheckoutPosition(const Position checked_position)
{
	for (auto info : robot_infos_)
	{
		if(info.position == checked_position)
		{
			return info.robot;
		}
	}
	return nullptr;
}

IGameView* Environment::GetView() const
{
	return view_;
}

Environment::~Environment()
{
	for(auto& info : robot_infos_)
	{
		delete info.robot;
	}
	delete view_;
}
