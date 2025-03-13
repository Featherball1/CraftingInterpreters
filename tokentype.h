#pragma once
#include <map>
#include <string>

enum TokenType {
	// Single-character
	LEFT_PAREN = 0, RIGHT_PAREN,
	LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT,
	MINUS, PLUS,
	SEMICOLON,
	SLASH,
	STAR,

	// One or two character
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals
	IDENTIFIER, STRING, NUMBER,

	// Keywords
	AND, CLASS, ELSE, FALSE, FOR, IF, NIL, OR, FUN, 
	PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	_EOF
};

extern std::map<TokenType, std::string> token_type_to_str_literal;