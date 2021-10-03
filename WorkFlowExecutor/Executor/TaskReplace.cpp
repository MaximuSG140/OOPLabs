#include "TaskReplace.h"
#include <string>

void TaskReplace::Complete(std::vector<std::string>& data)
{
	for(auto line: data)
	{
		while(line.find(keyWord) != std::string::npos)
		{
			size_t pos = line.find(keyWord);
			line.erase(pos, keyWord.length());
			line.insert(pos, toChange);
		}
	}
}
