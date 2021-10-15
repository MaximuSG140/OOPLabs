#include "BlockReader.h"
#include <functional>
#include "TaskReadFile.h"
#include "TaskWriteFile.h"
#include "TaskSort.h"
#include "TaskReplace.h"
#include "TaskDump.h"
#include "TaskGrep.h"
#include "CompileTimeExceptions.h"

std::map<int, Task*> BlockReader::ReadAllBlocks(const std::vector<Block>& blocks)
{
	std::map<int, Task*> res;
	for (size_t i = 0; i < blocks.size(); ++i)
	{
		if(blocks[i].number <= 0)
		{
			throw invalid_block_number(i + 1, std::string(std::_Integral_to_string<char>(blocks[i].number)));
		}
		if(blocks[i].assignment != "=")
		{
			throw invalid_assignment_sign(i + 1, blocks[i].assignment);
		}
		switch(blocks[i].operation)
		{
		case operations::read:
			if(blocks[i].arguments.size() != 1)
			{
				throw invalid_argument_ammount(i + 1, blocks[i].arguments.size(), 1);	
			}
			res[blocks[i].number] = new TaskReadFile(blocks[i].arguments[0]);
			break;
		case operations::write:
			if (blocks[i].arguments.size() != 1)
			{
				throw invalid_argument_ammount(i + 1, blocks[i].arguments.size(), 1);
			}
			res[blocks[i].number] = new TaskWriteFile(blocks[i].arguments[0]);
			break;
		case operations::grep:
			if (blocks[i].arguments.size() != 1)
			{
				throw invalid_argument_ammount(i + 1, blocks[i].arguments.size(), 1);
			}
			res[blocks[i].number] = new TaskGrep(blocks[i].arguments[0]);
			break;
		case operations::replace:
			if (blocks[i].arguments.size() != 2)
			{
				throw invalid_argument_ammount(i + 1, blocks[i].arguments.size(), 2);
			}
			res[blocks[i].number] = new TaskReplace(blocks[i].arguments[0], blocks[i].arguments[1]);
			break;
		case operations::dump:
			if (blocks[i].arguments.size() != 1)
			{
				throw invalid_argument_ammount(i + 1, blocks[i].arguments.size(), 1);
			}
			res[blocks[i].number] = new TaskDump(blocks[i].arguments[0]);
			break;
		case operations::sort:
			if (!blocks[i].arguments.empty())
			{
				throw invalid_argument_ammount(i + 1, blocks[i].arguments.size(), 0);
			}
			res[blocks[i].number] = new TaskSort();
			break;
		}
	}
	return res;
}