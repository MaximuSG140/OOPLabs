#pragma once
#include "Task.h"
#include <map>
#include <sstream>
#include <utility>

class NodeReader
{
public:
	NodeReader() = default;
	NodeReader(std::stringstream* sstream, std::map<int, Task*> taskMap):instructionStream(sstream), taskMap(
		                                                                      std::move(taskMap)){}
	~NodeReader();

	bool HasNodes();
	Task* ReadNext();
private:

	std::stringstream* instructionStream;
	std::map<int, Task*>taskMap;
};

