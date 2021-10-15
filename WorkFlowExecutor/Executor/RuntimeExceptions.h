#pragma once
#include <exception>
#include <string>

class runtime_error : public std::exception
{
public:
	runtime_error() = default;
};

class invalid_file_name : public runtime_error
{
public:
	invalid_file_name(std::string name):
		fileName(std::move(name)){}
private:
	std::string fileName;
};

class invalid_data_condition : public runtime_error
{
public:
	invalid_data_condition(bool isFilled):
		isFilled(isFilled){}
private:
	bool isFilled;
};

class invalid_node_number: public runtime_error
{
public:
	invalid_node_number(int wrongNumber):
		wrong(wrongNumber){}
private:
	int wrong;
};