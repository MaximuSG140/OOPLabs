#include "TaskGrep.h"
#include "RuntimeExceptions.h"

void TaskGrep::Complete(DataWrapper& shell)
{
	if(!shell.isFilled)
	{
		throw invalid_data_condition(false);
	}
	std::vector<std::string>newData;
	for(const auto& line : shell.data)
	{
		if(line.find(keyWord) != std::string::npos)
		{
			newData.push_back(line);
		}
	}
	shell.data = newData;
}
