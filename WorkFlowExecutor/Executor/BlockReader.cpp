#include "BlockReader.h"
#include <unordered_map>
#include <functional>
#include <set>
#include "TaskReadFile.h"
#include "TaskWriteFile.h"
#include "TaskSort.h"
#include "TaskReplace.h"
#include "TaskDump.h"
#include "TaskGrep.h"

BlockReader::~BlockReader()
{
	delete blockStream;
}

std::map<int, Task*> BlockReader::ReadAllBlocks()
{
	std::set<int> usedNumbers;
	std::string blockNumber;
	std::map<int, Task*> result;
	std::unordered_map<std::string, std::function<Task*()>> stringSwitch = { {"readfile", [&]()->Task*
	{
		std::string fileName;
		*blockStream >> fileName;
		return  new TaskReadFile(fileName);
	}
	}, {"writefile", [&]()->Task*
	{
		std::string fileName;
		*blockStream >> fileName;
		return new TaskWriteFile(fileName);
	}
	}, {"sort", [&]()->Task*
	{
		return new TaskSort();
	}
	}, {"dump", [&]()->Task*
	{
		std::string fileName;
		*blockStream >> fileName;
		return new TaskDump(fileName);
	}
	}, {"replace", [&]()->Task*
	{
		std::string keyWord, toChange;
		*blockStream >> keyWord >> toChange;
		return new TaskReplace(keyWord, toChange);
	}
	}, {"grep", [&]()->Task*
	{
		std::string keyWord;
		*blockStream >> keyWord;
		return new TaskGrep(keyWord);
	}
	} };
	while(*blockStream >> blockNumber)
	{
		int number = std::stoi(blockNumber);
		if(usedNumbers.count(number))
		{
			throw std::exception();		//TODO: add proper exception types for this case
		}
		std::string assignmentSign, currentWord;
		*blockStream >> assignmentSign >> currentWord;
		result[number] = stringSwitch[currentWord]();
		usedNumbers.insert(number);
	}
	return result;
}
