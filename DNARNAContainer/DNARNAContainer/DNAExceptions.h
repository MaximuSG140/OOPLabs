#pragma once
#include <exception>
class RNAs_are_not_complimentary : std::exception
{
public:
	char const* what()const override;
};

