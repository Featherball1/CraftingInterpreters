#pragma once
#include <map>
#include "tokentype.h"

/*
This file simply defines a map which maps lox keywords as strings to lox keywords as an enum
*/

namespace lox {
	extern std::map<std::string, TokenType> str_literal_to_lox_keywords;
}