#pragma once
#include <string>
#include <fstream>
#include "ConsoleView.h"

inline void GenerateMap(const std::string& file_name, const int width, const int height)
{
	std::ofstream file_stream(file_name);
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			int roll = rand() % 100;
			if(roll < 5)
			{
				file_stream << "^";
				continue;
			}
			if (roll < 20)
			{
				file_stream << "0";
				continue;
			}
			if (roll < 30)
			{
				file_stream << "*";
				continue;
			}
			file_stream << " ";
		}
		if (i != height - 1)
		{
			file_stream << std::endl;
		}
	}
}
