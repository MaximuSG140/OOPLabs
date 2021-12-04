#pragma once
#include <deque>
#include <vector>
#include <string>
#include "SmartRobot.h"

class LandscapeMap;
class IGameView;
class EnvironmentQuery;

struct Position;

struct RobotInfo
{
	Position position;
	SmartRobot* robot;
};

class Environment
{
public:
	explicit Environment(IGameView* game_view, const std::string& file_name);

	RobotInfo& GetRobotInfo(SmartRobot* search_id);
	LandscapeMap& GetMap();
	void RemoveRobot(SmartRobot* remove_id);
	void AskForNewOptions();
	void MakeTurn();
	void AddCollector();
	void AddSapper(SmartRobot* master);
	SmartRobot* CheckoutPosition(Position checked_position);
	IGameView* GetView() const;

	~Environment();
private:
	LandscapeMap real_map_;
	std::vector<RobotInfo> robot_infos_;
	std::deque<MessageWrapper> current_radio_messages_;
	std::deque<MessageWrapper> previous_radio_messages_;
	IGameView* view_;
};
