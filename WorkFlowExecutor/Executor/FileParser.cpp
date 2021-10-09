#include "FileParser.h"
#include "ParseExceptions.h"
#include "CompileTimeExceptions.h"
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

std::vector<Block> FileParser::GetBlocks(const std::string& fileName)
{
	std::ifstream targetFile(fileName);
	std::string currentLine;
	
	while(targetFile >> currentLine && currentLine != "desc"){}
	std::vector<Block> res;
	char* cStr = new char[1000];
	targetFile.getline(cStr, 1000);
	while(targetFile.getline(cStr, 1000) && std::string(cStr) != "csed")
	{
		std::stringstream sstream(cStr);
		Block newBlock;
		std::string number;
		sstream >> number;
		try
		{
			newBlock.number = std::stoi(number);
		}
		catch(std::exception&)
		{
			throw invalid_number(fileName, number);
		}
		sstream >> newBlock.assignment;
		std::string operationName;
		sstream >> operationName;
		if(operationName == "readfile")
		{
			newBlock.operation = operations::read;
		}else
		if(operationName == "writefile")
		{
			newBlock.operation = operations::write;
		}else
		if(operationName == "sort")
		{
			newBlock.operation = operations::sort;
		}else
		if(operationName == "grep")
		{
			newBlock.operation = operations::grep;
		}else
		if(operationName == "replace")
		{
			newBlock.operation = operations::replace;
		}else
		if(operationName == "dump")
		{
			newBlock.operation = operations::dump;
		}else
		{
			throw invalid_operation_name(fileName, operationName);
		}
		std::string arg;
		while(sstream >> arg)
		{
			newBlock.arguments.push_back(arg);
		}
		res.push_back(newBlock);
	}
	delete[] cStr;
	targetFile.close();
	return res;
}

std::vector<int> FileParser::GetSequence(const std::string& fileName)
{
	std::ifstream targetFile(fileName);
	std::string currentWord;
	while (targetFile >> currentWord && currentWord != "csed") {}
	std::vector<int> res;
	bool afterNumber = false;
	while (targetFile >> currentWord)
	{
		if (currentWord != "->")
		{
			if(afterNumber)
			{
				throw invalid_arrow(fileName, currentWord);
			}
			afterNumber = true;
			int number;
			try
			{
				number = std::stoi(currentWord);
			}
			catch (std::exception&)
			{
				throw invalid_number(fileName, currentWord);	
			}
			if (number <= 0)
			{
				throw invalid_number(fileName, std::_Integral_to_string<char>(number));
			}
			res.push_back(number);
		}
		else
		{
			if(!afterNumber)
			{
				throw invalid_number(fileName, currentWord);
			}
			afterNumber = false;
		}
		
	}
	targetFile.close();
	return res;
}

bool FileParser::HasCorrectDescription(const std::string& fileName)
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
	targetFile.close();
	return foundStart && foundEnd;
}
