#pragma once
#include <deque>
#include "SmartRobot.h"
#include "CollectResources.h"
#include "IGameView.h"

class Collector final:
	public SmartRobot
{
public:
	explicit Collector(std::deque<MessageWrapper>& message_sequence);

	void SetInspect(size_t number);
	void SetCollectResources();
	void SetRemote(IGameView* game_interface);

	std::string GetRole() override;
	EnvironmentQueryWrapper Push(Direction push_direction) override;
	EnvironmentQueryWrapper PerformAction() override;
protected:
	EnvironmentQueryWrapper OnBlow() override;
	void Collect();

private:
	size_t apples_collected_;
	RobotBehaviour* behaviour_ = nullptr;
};

