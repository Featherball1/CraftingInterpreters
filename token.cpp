#include "token.h"

lox::Token::Token(TokenType type, std::string lexeme, lox_literal_t literal, int line)
	: type(type), lexeme(lexeme), literal(literal), line(line)
{}

std::string lox::Token::to_string() {
	return token_type_to_str_literal[type] + " " + lexeme; //+static_cast<std::string>(literal);
}