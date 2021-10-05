#include "FileSplitter.h"
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

void FileSplitter::GetBlockPart(const std::string& fileName)
{
	std::ifstream targetFile(fileName);
	std::string currentLine;
	targetFile >> currentLine;
	if(currentLine != "desc")
	{
		targetFile.close();
		throw std::exception();		//TODO: Make proper exception class
	}
	std::ofstream res("BlockSequence.txt");
	char* cStr = new char[1000];
	targetFile.getline(cStr, 1000);
	while(targetFile.getline(cStr, 1000) && std::string(cStr) != "csed")
	{
		res << std::string(cStr) << std::endl;
	}
	delete cStr;
	targetFile.close();
	res.close();
}

void FileSplitter::GetNodePart(const std::string& fileName)
{
	std::ifstream targetFile(fileName);
	std::string currentWord;
	while(targetFile >> currentWord && currentWord != "csed"){}
	std::ofstream res("NodeSequence.txt");
	while(targetFile >> currentWord)
	{
		if(currentWord != "->")
		{
			int number;
			try
			{
				number = std::stoi(currentWord);
			}
			catch(std::exception&)
			{
				throw std::exception();		//TODO: add proper exception for this case
			}
			if(number <= 0)
			{
				throw std::exception();		//TODO: add proper exception for this case
			}
		}
		res << currentWord << " ";
	}
	targetFile.close();
	res.close();
}

bool FileSplitter::HasCorrectDescription(const std::string& fileName)
{
	std::ifstream targetFile(fileName);
	std::string currentWord;
	bool foundStart = false;
	bool foundEnd = false;
	while(targetFile >> currentWord)
	{
		if(currentWord == "desc" && foundStart == false)
		{
			foundStart = true;
		}
		else
		{
			if (currentWord == "desc")
			{
				return false;
			}
		}
		if(currentWord == "csed" && foundStart == true && foundEnd == false)
		{
			foundEnd = true;
		}
		else
		{
			if(currentWord == "csed")
			{
				return false;
			}
		}
	}
	return foundStart && foundEnd;
}
