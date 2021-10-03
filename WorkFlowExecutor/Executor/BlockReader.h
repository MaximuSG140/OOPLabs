#pragma once
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include "Task.h"

class BlockReader
{
public:
	BlockReader(std::stringstream* blockStream):blockStream(blockStream){}
	BlockReader() = default;
	~BlockReader();
	std::map<int, Task*>ReadAllBlocks();
private:
	
	std::stringstream* blockStream;
};

