#include "BlockReader.h"
#include <functional>
#include "TaskReadFile.h"
#include "TaskWriteFile.h"
#include "TaskSort.h"
#include "TaskReplace.h"
#include "TaskDump.h"
#include "TaskGrep.h"
#include "CompileTimeExceptions.h"

Task* CreateTask(operations operation, const std::vector<std::string>& arguments, const int line)
{
	switch (operation)
	{
	case operations::read:
		if (arguments.size() != 1)
		{
			throw invalid_argument_ammount(line + 1, arguments.size(), 1);
		}
		return new TaskReadFile(arguments[0]);
	case operations::write:
		if (arguments.size() != 1)
		{
			throw invalid_argument_ammount(line + 1, arguments.size(), 1);
		}
		return new TaskWriteFile(arguments[0]);
	case operations::grep:
		if (arguments.size() != 1)
		{
			throw invalid_argument_ammount(line + 1, arguments.size(), 1);
		}
		return new TaskGrep(arguments[0]);
	case operations::replace:
		if (arguments.size() != 2)
		{
			throw invalid_argument_ammount(line + 1, arguments.size(), 2);
		}
		return new TaskReplace(arguments[0], arguments[1]);
	case operations::dump:
		if (arguments.size() != 1)
		{
			throw invalid_argument_ammount(line + 1, arguments.size(), 1);
		}
		return new TaskDump(arguments[0]);
	case operations::sort:
		if (!arguments.empty())
		{
			throw invalid_argument_ammount(line + 1, arguments.size(), 0);
		}
		return new TaskSort();
	}
	return nullptr;
}


std::unordered_map<int, Task*> BlockReader::ReadAllBlocks(const std::vector<Block>& blocks)
{
	std::unordered_map<int, Task*> res;
	for (size_t i = 0; i < blocks.size(); ++i)
	{
		res[blocks[i].number] = CreateTask(blocks[i].operation, blocks[i].arguments, i);
	}
	return res;
}