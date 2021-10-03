#include "TaskGrep.h"

void TaskGrep::Complete(std::vector<std::string>&data)
{
	std::vector<std::string>newData;
	for(auto line:data)
	{
		if(line.find(keyWord) != std::string::npos)
		{
			newData.push_back(line);
		}
	}
	data = newData;
}
