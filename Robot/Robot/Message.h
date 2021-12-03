#pragma once

class SmartRobot;

class Message
{
public:
	virtual ~Message() = default;
	virtual void Receive(SmartRobot* receiver) = 0;
};

