#pragma once
#include "Message.h"

struct Position;

class MineExploded final :
	public Message
{
public:
	explicit MineExploded(Position explosion_place);
	void Receive(SmartRobot* receiver) override;
	~MineExploded() override = default;
private:
	Position place_;
};

