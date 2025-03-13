#pragma once
#include <string>
#include "tokentype.h"
#include "literal.h"

/*
Lexeme - smallest sequence of characters that represents something
Lexemes are raw substrings of source code.

Once lexemes are bundled together with other data, the result is a token.

Tokens can consist of:
	- TokenType
	- Literal value
	- Location Information
*/

class Token {
	const TokenType type;
	const std::string lexeme;
	const lox_literal_t literal;
	const int line;

public:
	Token(TokenType type, std::string lexeme, lox_literal_t literal, int line);
	std::string to_string();
};