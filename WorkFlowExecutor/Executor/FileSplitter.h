#pragma once
#include <string>

class FileSplitter
{
public:
	FileSplitter() = delete;
	static std::stringstream* GetBlockPart(const std::string&);
	static std::stringstream* GetNodePart(const std::string&);
};

