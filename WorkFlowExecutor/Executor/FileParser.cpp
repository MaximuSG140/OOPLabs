#include "FileParser.h"
#include "ParseExceptions.h"
#include "CompileTimeExceptions.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <sstream>
#include <fstream>
#include <exception>

std::unordered_map<std::string, operations>GetOperation
{
	{"writefile", operations::write},
	{"readfile", operations::read},
	{"grep", operations::grep},
	{"sort", operations::sort},
	{"dump", operations::dump},
	{"replace", operations::replace}
};

std::vector<Block> FileParser::GetBlocks(const std::string& fileName)
{
	std::ifstream targetFile(fileName);
	std::string currentLine;
	
	while(targetFile >> currentLine && currentLine != "desc"){}
	std::vector<Block> res;
	std::getline(targetFile, currentLine);
	while(std::getline(targetFile, currentLine) && currentLine != "csed")
	{
		std::stringstream words(currentLine);
		Block newBlock;
		std::string number;
		words >> number;
		try
		{
			newBlock.number = std::stoi(number);
		}
		catch(std::exception&)
		{
			throw invalid_number(fileName, number);
		}
		words >> newBlock.assignment;
		std::string operationName;
		words >> operationName;
		try
		{
			newBlock.operation = GetOperation[operationName];
		}
		catch(std::out_of_range&)
		{
			throw invalid_operation_name(fileName, operationName);
		}
		std::string arg;
		while(words >> arg)
		{
			newBlock.arguments.push_back(arg);
		}
		res.push_back(newBlock);
	}
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
	return foundStart && foundEnd;
}
