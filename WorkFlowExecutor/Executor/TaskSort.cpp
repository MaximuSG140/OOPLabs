#include "TaskSort.h"
#include <algorithm>

void TaskSort::Complete(DataWrapper& shell)
{
	if(!shell.isFilled)
	{
		throw invalid_data_condition(false);
	}
	std::sort(shell.data.begin(), shell.data.end());
}
