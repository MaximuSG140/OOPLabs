#include "RNAExceptions.h"
#include <string>

char const* invalid_index_exception::what() const
{
	std::string msg;
	msg += "Invalid index:\nMinimal allowed value: ";
	char* minIndexStr = new char[32];
	_itoa_s(minimumIndex, minIndexStr, 32, 10);
	msg += minIndexStr;
	msg += "\nMaximal allowed value: ";
	char* maxIndexStr = new char[32];
	_itoa_s(maximumIndex, maxIndexStr, 32, 10);
	msg += maxIndexStr;
	msg += "\nUsed index: ";
	char* indexStr = new char[32];
	_itoa_s(index, indexStr, 32, 10);
	msg += indexStr;
	delete[] minIndexStr;
	delete[] maxIndexStr;
	delete[] indexStr;
	char* cstringMsg = new char[msg.length()];
	for(unsigned int i = 0; i < msg.length(); ++i)
	{
		cstringMsg[i] = msg[i];
	}
	return cstringMsg;
}

bool invalid_index_exception::operator==(const invalid_index_exception& e) const
{
	return index == e.index && minimumIndex == e.minimumIndex && maximumIndex == maximumIndex;
}
