#include "insufficient_fuel_error.h"
#pragma warning(disable :4996)

insufficient_fuel_error::insufficient_fuel_error(const char* message) :logic_error(message)
{
	_message = new char[strlen(message) + 1];
	strcpy(_message, message);
};
const char* insufficient_fuel_error::what()const
{
	return _message;
}