#include "UserCommandWrapper.h"

UserCommandWrapper::UserCommandWrapper(UserCommand* cmd) :
	cmd_(cmd)
{}

void UserCommandWrapper::Perform(Environment* env) const
{
	cmd_->Respond(env);
}

UserCommandWrapper::~UserCommandWrapper()
{
	delete cmd_;
}

UserCommandWrapper::UserCommandWrapper(UserCommandWrapper&& other) noexcept
{
	cmd_ = other.cmd_;
	other.cmd_ = nullptr;
}

UserCommandWrapper& UserCommandWrapper::operator=(UserCommandWrapper&& other) noexcept
{
	std::swap(cmd_, other.cmd_);
	return *this;
}
