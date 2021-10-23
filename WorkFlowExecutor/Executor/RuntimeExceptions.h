#pragma once
#include <exception>
#include <string>

class RuntimeError : public std::exception
{
public:
	RuntimeError() = default;
};

class InvalidFileName final : public RuntimeError
{
public:
	explicit InvalidFileName(std::string name):
		fileName(std::move(name)){}
private:
	std::string fileName;
};

class InvalidDataCondition final : public RuntimeError
{
public:
	explicit InvalidDataCondition(const bool isFilled):
		isFilled(isFilled){}
private:
	bool isFilled;
};

class InvalidNodeNumber final : public RuntimeError
{
public:
	explicit InvalidNodeNumber(const int wrongNumber):
		wrong(wrongNumber){}
private:
	int wrong;
};