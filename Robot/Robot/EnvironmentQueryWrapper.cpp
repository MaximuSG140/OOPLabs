#include "EnvironmentQueryWrapper.h"

#include <algorithm>

EnvironmentQueryWrapper::EnvironmentQueryWrapper(EnvironmentQuery* query) :
	query_(query)
{}

void EnvironmentQueryWrapper::Apply(Environment* env) const
{
	if (query_ != nullptr)
	{
		query_->Perform(env);
	}
}

EnvironmentQueryWrapper::EnvironmentQueryWrapper(EnvironmentQueryWrapper&& other) noexcept
{
	query_ = other.query_;
	other.query_ = nullptr;
}

EnvironmentQueryWrapper& EnvironmentQueryWrapper::operator=(EnvironmentQueryWrapper&& other) noexcept
{
	std::swap(query_, other.query_);
	return *this;
}

EnvironmentQueryWrapper::~EnvironmentQueryWrapper()
{
	delete query_;
}
