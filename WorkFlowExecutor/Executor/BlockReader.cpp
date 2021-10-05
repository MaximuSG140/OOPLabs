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

std::map<int, Task*> BlockReader::ReadAllBlocks()
{
	std::set<int> usedNumbers;
	std::string blockNumber;
	std::map<int, Task*> result;
	std::ifstream blockStream(fileName);
	std::unordered_map<std::string, std::function<Task*()>> stringSwitch = { {"readfile", [&]()->Task*
	{
		std::string fileName;
		blockStream >> fileName;
		return  new TaskReadFile(fileName);
	}
	}, {"writefile", [&]()->Task*
	{
		std::string fileName;
		blockStream >> fileName;
		return new TaskWriteFile(fileName);
	}
	}, {"sort", [&]()->Task*
	{
		return new TaskSort();
	}
	}, {"dump", [&]()->Task*
	{
		std::string fileName;
		blockStream >> fileName;
		return new TaskDump(fileName);
	}
	}, {"replace", [&]()->Task*
	{
		std::string keyWord, toChange;
		blockStream >> keyWord >> toChange;
		return new TaskReplace(keyWord, toChange);
	}
	}, {"grep", [&]()->Task*
	{
		std::string keyWord;
		blockStream >> keyWord;
		return new TaskGrep(keyWord);
	}
	} };
	while(blockStream >> blockNumber)
	{
		int number = std::stoi(blockNumber);
		if(usedNumbers.count(number))
		{
			throw std::exception();		//TODO: add proper exception types for this case
		}
		std::string assignmentSign, currentWord;
		blockStream >> assignmentSign >> currentWord;
		result[number] = stringSwitch[currentWord]();
		usedNumbers.insert(number);
	}
	blockStream.close();
	return result;
}

bool BlockReader::IsCorrect(const std::string& fileName)
{
	std::set<int>blockNumbers;
	std::unordered_map<std::string, int>argsAmmount = { {"readfile", 1}, {"writefile", 1}, {"grep", 1}, {"replace", 2}, {"sort", 0}, {"dump", 1} };
	std::ifstream targetFile(fileName);
	std::string currentNumber;
	std::string assign;
	while(targetFile >> currentNumber)
	{
		targetFile >> assign;
		if(assign != "=")
		{
			return false;		//after number not '='
		}
		try
		{
			std::stoi(currentNumber);
		}
		catch (std::exception&)
		{
			return false;		//incorrect number
		}
		std::string operation;
		targetFile >> operation;
		std::string arguments[2];
		if(blockNumbers.count(std::stoi(currentNumber)))
		{
			return false;		//block collision
		}
		blockNumbers.insert(std::stoi(currentNumber));
		try 
		{
			for (int i = 0; i < argsAmmount[operation]; ++i)
			{
				targetFile >> arguments[i];
				if (arguments[i].empty())
				{
					return false;	//incorrect args
				}
			}
		}
		catch(std::exception&)
		{
			return false;	//no such operation
		}
	}
	targetFile.close();
	return true;
}
