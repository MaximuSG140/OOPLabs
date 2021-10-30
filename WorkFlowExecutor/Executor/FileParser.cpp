#include "FileParser.h"
#include "ParseExceptions.h"
#include "CompileTimeExceptions.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <sstream>
#include <fstream>
#include <exception>

std::vector<Block> FileParser::GetBlocks(const std::string& fileName)
{
	if(!HasCorrectDescription(fileName))
	{
		throw InvalidDescriptionBlock(fileName);
	}

	std::ifstream targetFile(fileName);
	std::string currentLine;
	std::vector<Block> res;
	
	while(std::getline(targetFile, currentLine) && currentLine != "desc"){}

	int descLine = 1;
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
			throw InvalidNumber(fileName, number);
		}
		if(newBlock.number <= 0)
		{
			throw InvalidNumber(fileName, number);
		}

		std::string assignment;
		words >> assignment;
		if(assignment != "=")
		{
			throw InvalidAssignmentSign(descLine, assignment);
		}

		std::unordered_map<std::string, operations>getOperation
		{
			{"writefile", operations::write},
			{"readfile", operations::read},
			{"grep", operations::grep},
			{"sort", operations::sort},
			{"dump", operations::dump},
			{"replace", operations::replace}
		};
		std::string operationName;
		words >> operationName;
		try
		{
			newBlock.operation = getOperation.at(operationName);
		}
		catch(std::out_of_range&)
		{
			throw InvalidOperationName(fileName, operationName);
		}

		std::string arg;
		while(words >> arg)
		{
			newBlock.arguments.push_back(arg);
		}

		res.push_back(newBlock);
		descLine++;
	}
	return res;
}

std::queue<int> FileParser::GetSequence(const std::string& fileName)
{
	if (!HasCorrectDescription(fileName))
	{
		throw InvalidDescriptionBlock(fileName);
	}

	std::ifstream targetFile(fileName);
	std::string currentWord, currentLine;

	while (std::getline(targetFile, currentLine) && currentLine != "csed") {}

	std::queue<int> res;
	bool afterNumber = false;

	while (targetFile >> currentWord)
	{
		if (currentWord != "->")
		{
			if(afterNumber)
			{
				throw InvalidArrow(fileName, currentWord);
			}
			afterNumber = true;

			int number;
			try
			{
				number = std::stoi(currentWord);
			}
			catch (std::exception&)
			{
				throw InvalidNumber(fileName, currentWord);	
			}
			if (number <= 0)
			{
				throw InvalidNumber(fileName, currentWord);
			}
			res.push(number);
		}
		else
		{
			if(!afterNumber)
			{
				throw InvalidNumber(fileName, currentWord);
			}
			afterNumber = false;
		}
		
	}
	return res;
}

bool FileParser::HasCorrectDescription(const std::string& fileName)
{
	std::ifstream targetFile(fileName);
	std::string currentLine;
	bool foundStart = false;
	bool foundEnd = false;

	while(std::getline(targetFile, currentLine))
	{
		if(currentLine == "desc" && foundStart == false)
		{
			foundStart = true;
		}
		else
		{
			if (currentLine == "desc")
			{
				return false;
			}
		}
		if(currentLine == "csed" && foundStart == true && foundEnd == false)
		{
			foundEnd = true;
		}
		else
		{
			if(currentLine == "csed")
			{
				return false;
			}
		}
	}
	return foundStart && foundEnd;
}