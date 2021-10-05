#pragma once
#include <string>
#include <fstream>
#include <map>
#include "Task.h"

class BlockReader
{
public:
	BlockReader(const std::string& fileName):fileName(fileName){}
	BlockReader() = default;

	std::map<int, Task*>ReadAllBlocks();

	static bool IsCorrect(const std::string& fileName);
private:
	std::string fileName;
};

