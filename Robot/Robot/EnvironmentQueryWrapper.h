#pragma once
#include "EnvironmentQuery.h"

class EnvironmentQueryWrapper
{
public:
	EnvironmentQueryWrapper() = default;
	explicit EnvironmentQueryWrapper(EnvironmentQuery* query);
	void Apply(Environment* env) const;

	EnvironmentQueryWrapper(EnvironmentQueryWrapper&& other)noexcept;
	EnvironmentQueryWrapper& operator=(EnvironmentQueryWrapper&& other)noexcept;
	EnvironmentQueryWrapper& operator=(const EnvironmentQueryWrapper& other) = delete;
	EnvironmentQueryWrapper(const EnvironmentQueryWrapper& other) = delete;
	~EnvironmentQueryWrapper();
private:
	EnvironmentQuery* query_ = nullptr;
};

