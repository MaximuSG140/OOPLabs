#pragma once
#include <string>
#include <vector>
#include <queue>

enum class operations{read, write, grep, replace, dump, sort};

struct Block
{
	int number;
	operations operation;
	std::vector<std::string>arguments;
};

class FileParser
{
public:
	FileParser() = delete;

	static std::vector<Block> GetBlocks(const std::string&);
	static std::queue<int> GetSequence(const std::string&);

	static bool HasCorrectDescription(const std::string&);
};

