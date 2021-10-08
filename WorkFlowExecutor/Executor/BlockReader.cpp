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

std::map<int, Task*> BlockReader::ReadAllBlocks(const std::vector<Block>& blocks)
{
	std::map<int, Task*> res;
	for (const auto& block : blocks)
	{
		if(block.number <= 0)
		{
			throw std::exception(); //TODO: add proper exception
		}
		if(block.assignment != "=")
		{
			throw std::exception();
		}
		switch(block.operation)
		{
		case operations::read:
			if(block.arguments.size() != 1)
			{
				throw std::exception();	//TODO: add proper exception
			}
			res[block.number] = new TaskReadFile(block.arguments[0]);
			break;
		case operations::write:
			if (block.arguments.size() != 1)
			{
				throw std::exception();	//TODO: add proper exception
			}
			res[block.number] = new TaskWriteFile(block.arguments[0]);
			break;
		case operations::grep:
			if (block.arguments.size() != 1)
			{
				throw std::exception();	//TODO: add proper exception
			}
			res[block.number] = new TaskGrep(block.arguments[0]);
			break;
		case operations::replace:
			if (block.arguments.size() != 2)
			{
				throw std::exception();	//TODO: add proper exception
			}
			res[block.number] = new TaskReplace(block.arguments[0], block.arguments[1]);
			break;
		case operations::dump:
			if (block.arguments.size() != 1)
			{
				throw std::exception();	//TODO: add proper exception
			}
			res[block.number] = new TaskDump(block.arguments[0]);
			break;
		case operations::sort:
			if (!block.arguments.empty())
			{
				throw std::exception();	//TODO: add proper exception
			}
			res[block.number] = new TaskSort();
			break;
		}
	}
	return res;
}