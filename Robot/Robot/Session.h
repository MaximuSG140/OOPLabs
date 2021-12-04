#pragma once
#include "Collector.h"
#include "IGameView.h"

class Session
{
public:
	explicit Session(IGameView*, const std::string&);
	void Start();
private:
	LandscapeMap map;
	Collector robot;
	IGameView* view;
};

