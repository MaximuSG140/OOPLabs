#pragma once
#include "UserCommand.h"

class UserCommandWrapper
{
public:
	UserCommandWrapper();
	explicit UserCommandWrapper(UserCommand* cmd);
	void Perform(Environment* env) const;
	~UserCommandWrapper();

	explicit operator bool()const;

	UserCommandWrapper(UserCommandWrapper&& other) noexcept;
	UserCommandWrapper& operator=(UserCommandWrapper&& other) noexcept;
	UserCommandWrapper(const UserCommandWrapper& other) = delete;
	UserCommandWrapper& operator=(const UserCommandWrapper& other) = delete;
private:
	UserCommand* cmd_ = nullptr;
};

