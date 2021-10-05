#pragma once
#include "Task.h"
#include <map>
#include <fstream>
#include <utility>

class NodeReader
{
public:
	NodeReader() = default;
	NodeReader(const std::string& fileName, std::map<int, Task*>taskMap):instructionStream(fileName), taskMap(
		                                                                      std::move(taskMap)){}

	bool HasNodes() const;
	Task* ReadNext();

	static bool IsCorrect(const std::string&, std::map<int, Task*> taskMap);
private:

	std::ifstream instructionStream;
	std::map<int, Task*>taskMap;
};

