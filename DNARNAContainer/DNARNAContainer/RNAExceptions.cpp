#include "RNAExceptions.h"
#include <string>

char const* invalid_index_exception::what() const
{
	std::string msg;
	msg += "Invalid index:\nMinimal allowed value:";
	char* minIndexStr[32];
	_itoa_s(minimumIndex, minIndexStr, 32, 10);
	msg += minIndexStr;
	return "Invalid index:";
}
