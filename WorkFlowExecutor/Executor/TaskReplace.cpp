#include "TaskReplace.h"
#include <string>
#include <sstream>
#include "RuntimeExceptions.h"

void TaskReplace::Complete(DataWrapper& shell, const std::vector<std::string>& arguments)const
{
	if(!shell.isFilled)
	{
		throw InvalidDataCondition(false);
	}

	for (auto& line : shell.data)
	{
		std::stringstream words(line);
		std::string word;
		std::string newLine;
		while(words >> word)
		{
			if (!newLine.empty())
			{
				newLine += " ";
			}
			if(word == arguments[0])
			{
				newLine += arguments[1];
			}
			else
			{
				newLine += word;
			}
		}
		line = newLine;
	}
}
