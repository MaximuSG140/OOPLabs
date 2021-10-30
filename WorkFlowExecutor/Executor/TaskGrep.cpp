#include "TaskGrep.h"
#include "RuntimeExceptions.h"
#include <sstream>

void TaskGrep::Complete(DataWrapper& shell, const std::vector<std::string>& arguments)const
{
	if(!shell.isFilled)
	{
		throw InvalidDataCondition(false);
	}

	std::vector<std::string>newData;
	for(const auto& line : shell.data)
	{
		std::stringstream words(line);
		std::string currentWord;

		while(words >> currentWord)
		{
			if(currentWord == arguments[0])
			{
				newData.push_back(line);
				break;
			}
		}
	}
	shell.data = newData;
}
