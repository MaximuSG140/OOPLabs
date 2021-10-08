#pragma once
#include <string>
#include <fstream>
#include <map>
#include "Task.h"
#include "FileParser.h"

class BlockReader
{
public:
	BlockReader() = delete;
	static std::map<int, Task*>ReadAllBlocks(const std::vector<Block>&);
private:
};

