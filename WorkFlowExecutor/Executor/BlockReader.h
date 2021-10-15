#pragma once
#include <string>
#include <unordered_map>
#include "Task.h"
#include "FileParser.h"

class BlockReader
{
public:
	BlockReader() = delete;
	static std::unordered_map<int, Task*>ReadAllBlocks(const std::vector<Block>&);
};

