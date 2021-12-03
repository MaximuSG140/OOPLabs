#include "Environment.h"
#include "Collector.h"
#include "ConsoleView.h"

int main()
{
	Environment e(new ConsoleView(), "in.txt");
	while(true)
	{
		e.MakeTurn();
	}
	return 0;
}