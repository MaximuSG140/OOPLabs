#include "MessageWrapper.h"
#include <algorithm>

MessageWrapper::MessageWrapper(SmartRobot* sender, Message* msg) :
	msg_(msg),
	sender_(sender)
{}

Message* MessageWrapper::Msg() const
{
	return msg_;
}

SmartRobot* MessageWrapper::Sender() const
{
	return sender_;
}

MessageWrapper::MessageWrapper(MessageWrapper&& other) noexcept
{
	msg_ = other.msg_;
	sender_ = other.sender_;
	other.msg_ = nullptr;
}

MessageWrapper& MessageWrapper::operator=(MessageWrapper&& other) noexcept
{
	std::swap(msg_, other.msg_);
	std::swap(sender_, other.sender_);
	return *this;
}

MessageWrapper::~MessageWrapper()
{
	delete msg_;
}
