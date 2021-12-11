#pragma once
#include "Message.h"

class MessageWrapper
{
public:
	explicit MessageWrapper(SmartRobot* sender, Message* msg);
	Message* Msg()const;
	SmartRobot* Sender()const;
	MessageWrapper(MessageWrapper&& other)noexcept;
	MessageWrapper& operator=(MessageWrapper&& other)noexcept;
	MessageWrapper(const MessageWrapper& other) = delete;
	MessageWrapper& operator=(const MessageWrapper& other) = delete;
	~MessageWrapper();
private:
	Message* msg_;
	SmartRobot* sender_;
};

