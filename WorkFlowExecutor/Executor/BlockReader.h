#pragma once
#include <string>
#include <unordered_map>
#include "Task.h"
#include "FileParser.h"
#include "NodeReader.h"

class BlockReader
{
public:
	BlockReader() = delete;
	static std::unordered_map<int, Action> ReadAllBlocks(const std::vector<Block>&,
	                                                     const std::unordered_map<operations, Task*>& taskGetter);

};
