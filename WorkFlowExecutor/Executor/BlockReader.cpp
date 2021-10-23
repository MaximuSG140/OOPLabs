#include "BlockReader.h"
#include <functional>
#include "CompileTimeExceptions.h"
#include "NodeReader.h"

Action CreateAction(const operations operation, const std::vector<std::string>& arguments, const int line,
                    std::unordered_map<operations, Task*> taskGetter)
{
	switch (operation)
	{
	case operations::read:
		if (arguments.size() != 1)
		{
			throw InvalidArgumentAmmount(line + 1, arguments.size(), 1);
		}
		return Action(taskGetter[operation], arguments);
	case operations::write:
		if (arguments.size() != 1)
		{
			throw InvalidArgumentAmmount(line + 1, arguments.size(), 1);
		}
		return Action(taskGetter[operation], arguments);
	case operations::grep:
		if (arguments.size() != 1)
		{
			throw InvalidArgumentAmmount(line + 1, arguments.size(), 1);
		}
		return Action(taskGetter[operation], arguments);
	case operations::replace:
		if (arguments.size() != 2)
		{
			throw InvalidArgumentAmmount(line + 1, arguments.size(), 2);
		}
		return Action(taskGetter[operation], arguments);
	case operations::dump:
		if (arguments.size() != 1)
		{
			throw InvalidArgumentAmmount(line + 1, arguments.size(), 1);
		}
		return Action(taskGetter[operation], arguments);
	case operations::sort:
		if (!arguments.empty())
		{
			throw InvalidArgumentAmmount(line + 1, arguments.size(), 0);
		}
		return Action(taskGetter[operation], arguments);
	}
	return Action(taskGetter[operation], arguments);
}


std::unordered_map<int, Action> BlockReader::ReadAllBlocks(const std::vector<Block>& blocks,
                                                           std::unordered_map<operations, Task*>& taskGetter)
{
	std::unordered_map<int, Action> res;
	for (size_t i = 0; i < blocks.size(); ++i)
	{
		res[blocks[i].number] = CreateAction(blocks[i].operation, blocks[i].arguments, i, taskGetter);
	}
	return res;
}
