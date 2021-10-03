#include "TaskSort.h"
#include <algorithm>

void TaskSort::Complete(std::vector<std::string>& data)
{
	std::sort(data.begin(), data.end());
}
