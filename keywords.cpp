#include "keywords.h"

std::map<std::string, lox::TokenType> lox::str_literal_to_lox_keywords = {
	{"and", TokenType::AND},
	{"class", TokenType::CLASS},
	{"else", TokenType::ELSE},
	{"false", TokenType::FALSE},
	{"for", TokenType::FOR},
	{"fun", TokenType::FUN},
	{"if", TokenType::IF},
	{"nil", TokenType::NIL},
	{"or", TokenType::OR},
	{"print", TokenType::PRINT},
	{"return", TokenType::RETURN},
	{"super", TokenType::SUPER},
	{"this", TokenType::THIS},
	{"true", TokenType::TRUE},
	{"var", TokenType::VAR},
	{"while", TokenType::WHILE}
};