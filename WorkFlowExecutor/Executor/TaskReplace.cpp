#include "TaskReplace.h"
#include <string>
#include <sstream>
#include "RuntimeExceptions.h"

void TaskReplace::Complete(DataWrapper& shell)
{
	if(!shell.isFilled)
	{
		throw invalid_data_condition(false);
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
			if(word == keyWord)
			{
				newLine += toChange;
			}
			else
			{
				newLine += word;
			}
		}
		line = newLine;
	}
}
