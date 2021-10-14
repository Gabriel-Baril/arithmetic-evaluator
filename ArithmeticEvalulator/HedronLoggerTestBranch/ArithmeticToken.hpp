#pragma once
#include <string>
#include "TokenType.hpp"

struct ArithmeticToken
{
	std::string value;
	token_type type;
};