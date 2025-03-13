#pragma once
#include <string>
#include <vector>
#include "token.h"
#include "literal.h"
#include "error.h"
#include "keywords.h"

class Scanner {
private:
	std::string source;
	std::vector<Token> tokens;

	/*
	These variables track the state of the scanner
		start: start character idx in source string
		current: current character idx in source string
		line: current line we are on in source string
	*/
	
	int start = 0;
	int current = 0;
	int line = 1;

	/*
	These are helpers for stepping through the source string
		advance: step us along by one character in the source string
		is_at_end: test if we are at the end of the source string
		match: a conditional advance. We only consume the current character if it matches the expected next character
		peek: look ahead to the next character without consuming
		peek_next: look twice ahead without consuming
	*/
	char advance();
	bool is_at_end();
	bool match(char expected);
	char peek();
	char peek_next();

	/*
	Functions 
		scan_token: scanning a token for its type
		add_token: add a token to the std::vector<Token> of tokens
	*/
	void scan_token();
	void add_token(TokenType type);
	void add_token(TokenType type, lox_literal_t literal);
	
	/*
	Handling literals.
	Once we detect a literal, branch off into one of these methods to generate the correct token. 
	*/
	void string();
	void number();
	void identifier();
	void block_comment();

	/*
	Helpers. 
	*/
	bool is_digit(char c);
	bool is_alpha(char c);
	bool is_alphanumeric(char c);

public:
	Scanner(std::string source);
	std::vector<Token> scan_tokens();
};