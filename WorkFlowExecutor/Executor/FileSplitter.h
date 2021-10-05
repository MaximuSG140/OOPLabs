#pragma once
#include <string>

class FileSplitter
{
public:
	FileSplitter() = delete;
	static void GetBlockPart(const std::string&);
	static void GetNodePart(const std::string&);
	static bool HasCorrectDescription(const std::string&);
};

