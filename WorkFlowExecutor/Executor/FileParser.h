#pragma once
#include <string>
#include <vector>

enum class operations{read, write, grep, replace, dump, sort};

struct Block
{
	int number;
	std::string assignment;
	operations operation;
	std::vector<std::string>arguments;
};

class FileParser
{
public:
	FileParser() = delete;

	static std::vector<Block> GetBlocks(const std::string&);
	static std::vector<int> GetSequence(const std::string&);

	static bool HasCorrectDescription(const std::string&);
};

