#pragma once
#include <vector>

struct DataWrapper
{
	bool isFilled;
	std::vector<std::string>data;
	DataWrapper();
};

inline DataWrapper::DataWrapper()
{
	isFilled = false;
}