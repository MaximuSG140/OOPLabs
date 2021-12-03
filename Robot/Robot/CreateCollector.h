#pragma once
#include "UserCommand.h"


class CreateCollector final :
	public UserCommand
{
	void Respond(Environment* env) override;
};

