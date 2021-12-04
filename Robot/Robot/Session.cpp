#include "Session.h"
#include <iostream>


Session::Session(IGameView* view, const std::string& fileName) :
	map(fileName),
	robot(map, view),
	view(view)
{}

void Session::Start()
{
	try
	{
		while (true)
		{
			view->DrawCachedMap(robot);
			robot.PerformAction();
			if (robot.GetSapper() != nullptr)
			{
				robot.GetSapper()->PerformAction();
			}
		}
	}
	catch(std::exception& e)
	{
		std::cout << "Session ended" << std::endl;
	}
}
