#include "TaskSort.h"
#include <algorithm>
#include "RuntimeExceptions.h"

void TaskSort::Complete(DataWrapper& shell, const std::vector<std::string>& arguments)const
{
	if(!shell.isFilled)
	{
		throw InvalidDataCondition(false);
	}

	std::sort(shell.data.begin(), shell.data.end());
}
