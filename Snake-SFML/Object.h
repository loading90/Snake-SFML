#pragma once
#include <SFML\Graphics.hpp>

const int CHUNK_SIZE = 20;
const int FIELD_SIZE = 20;

class Error
{
public:
	int code;
	std::string errorMessage;

	Error(int code, std::string message)
	{
		this->code = code;
		this->errorMessage = message;
	}
};
