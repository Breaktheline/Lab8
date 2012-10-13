#ifndef H_COMMON
#define H_COMMON

#include <stdlib.h>

struct ErrorMessages
{
	static const char* MEMORY_ERROR;
	static const char* FILE_OPEN_ERROR;
	static const char* WRONG_INPUT_ERROR;
};

const char* ErrorMessages::MEMORY_ERROR = "Can't allocate memory";
const char* ErrorMessages::FILE_OPEN_ERROR = "Can't open file";
const char* ErrorMessages::WRONG_INPUT_ERROR = "Wrong input format.";

class AppException 
{
public:
	AppException(const char* message)
	{
		_message = message;
	}

	const char* GetMessage() 
	{ 
		return _message;
	};
private:
	const char* _message;
};


#endif


