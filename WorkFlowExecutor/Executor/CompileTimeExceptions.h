#pragma once
#include <exception>
#include <string>
#include <utility>

class compile_error : public std::exception
{
public:
	compile_error(int line):lineNumber(line){}
private:
	int lineNumber;
};

class invalid_block_number : public compile_error
{
public:
	invalid_block_number(int line, std::string name):compile_error(line), wrongNumber(std::move(name)){}
private:
	std::string wrongNumber;
};

class invalid_assignment_sign : public compile_error
{
public:
	invalid_assignment_sign(int line, std::string sign):compile_error(line), wrongSign(std::move(sign)){}
private:
	std::string wrongSign;
};

class invalid_argument_ammount : public compile_error
{
public:
	invalid_argument_ammount(int line, size_t ammount, size_t expected):compile_error(line), ammount(ammount), expected(expected){}
private:
	size_t ammount;
	size_t expected;
};