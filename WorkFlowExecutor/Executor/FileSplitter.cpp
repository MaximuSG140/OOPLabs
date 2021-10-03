#include "FileSplitter.h"
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

std::stringstream* FileSplitter::GetBlockPart(const std::string& fileName)
{
	std::ifstream targetFile(fileName);
	std::string currentLine;
	targetFile >> currentLine;
	if(currentLine != "desc")
	{
		targetFile.close();
		throw std::exception();		//TODO: Make proper exception class
	}
	std::stringstream* res = new std::stringstream();
	while(targetFile >> currentLine && currentLine != "csed")
	{
		*res << currentLine;
	}
	targetFile.close();
	return res;
}

std::stringstream* FileSplitter::GetNodePart(const std::string& fileName)
{
	std::ifstream targetFile(fileName);
	std::string currentLine;
	while(targetFile >> currentLine && currentLine != "csed"){}
	std::stringstream* res = new std::stringstream();
	while(targetFile >> currentLine)
	{
		*res << currentLine;
	}
	return res;
}
