#include <iostream>
#include "Environment.h"
#include "Collector.h"
#include "ConsoleView.h"
#include "GenerateMap.h"

int main()
{
	GenerateMap("in.txt", 1000, 1000);
	Environment environment(new ConsoleView(), "in.txt");
	try
	{
		while (true)
		{
			environment.MakeTurn();
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Critical error:" << std::endl;
		std::cout << e.what() << std::endl;
	}
	return 0;
}