#include "TaskGrep.h"
#include "RuntimeExceptions.h"
#include <sstream>

void TaskGrep::Complete(DataWrapper& shell)
{
	if(!shell.isFilled)
	{
		throw invalid_data_condition(false);
	}

	std::vector<std::string>newData;
	for(const auto& line : shell.data)
	{
		std::stringstream words(line);
		std::string currentWord;

		while(words >> currentWord)
		{
			if(currentWord == keyWord)
			{
				newData.push_back(line);
				break;
			}
		}
	}
	shell.data = newData;
}
