#pragma once
#include <exception>
#include <string>

class parsing_error : public std::exception
{
public:
	parsing_error(std::string name):
		fileName(std::move(name)){}
private:
	std::string fileName;
};

class invalid_description_block: public parsing_error
{
public:
	invalid_description_block(const std::string& name):
		parsing_error(name){}
};

class invalid_number : public parsing_error
{
public:
	invalid_number(const std::string& fileName, std::string notInteger):
		parsing_error(fileName),
		notInteger(std::move(notInteger)){}
private:
	std::string notInteger;
};

class invalid_operation_name : public parsing_error
{
public:
	invalid_operation_name(const std::string& fileName, std::string name):
		parsing_error(fileName),
		operationName(std::move(name)) {}
private:
	std::string operationName;
};

class invalid_arrow : public parsing_error
{
public:
	invalid_arrow(const std::string& fileName, std::string word):
		parsing_error(fileName),
		notArrow(std::move(word)){}
private:
	std::string notArrow;
};
