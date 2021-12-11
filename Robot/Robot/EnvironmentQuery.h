#pragma once

class Environment;

class EnvironmentQuery
{
public:
	virtual ~EnvironmentQuery() = default;
	virtual void Perform(Environment* env) = 0;
};

