#pragma once
#include "UserCommand.h"

class UserCommandWrapper
{
public:
	explicit UserCommandWrapper(UserCommand* cmd);
	void Perform(Environment* env) const;
	~UserCommandWrapper();

	UserCommandWrapper(UserCommandWrapper&& other) noexcept;
	UserCommandWrapper& operator=(UserCommandWrapper&& other) noexcept;
	UserCommandWrapper(const UserCommandWrapper& other) = delete;
	UserCommandWrapper& operator=(const UserCommandWrapper& other) = delete;
private:
	UserCommand* cmd_ = nullptr;
};

