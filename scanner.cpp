#include "scanner.h"

lox::Scanner::Scanner(std::string source) : source(source) {}

bool lox::Scanner::is_at_end() {
	return (current >= source.length());
}

void lox::Scanner::scan_token() {
	char c = advance();

	/*
	The following tokens are all single characters and can be directly added. 
	*/
	if (c == '(') {
		add_token(TokenType::LEFT_PAREN);
	}
	else if (c == ')') {
		add_token(TokenType::RIGHT_PAREN);
	}
	else if (c == '{') {
		add_token(TokenType::LEFT_BRACE);
	}
	else if (c == '}') {
		add_token(TokenType::RIGHT_BRACE);
	}
	else if (c == ',') {
		add_token(TokenType::COMMA);
	}
	else if (c == '.') {
		add_token(TokenType::DOT);
	}
	else if (c == '-') {
		add_token(TokenType::MINUS);
	}
	else if (c == '+') {
		add_token(TokenType::PLUS);
	}
	else if (c == ';') {
		add_token(TokenType::SEMICOLON);
	}
	else if (c == '*') {
		add_token(TokenType::STAR);
	}
	/*
	The following tokens can be single characters or two and change meaning in each case
	The match function performs a conditional advance depending on if we are in one of those cases
	A special case is '/' which can become division or a comment.
	In the case of a comment, we advance until we hit the end of the line. 
	*/
	else if (c == '!') {
		add_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
	}
	else if (c == '=') {
		add_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
	}
	else if (c == '<') {
		add_token(match('<') ? TokenType::LESS_EQUAL : TokenType::LESS);
	}
	else if (c == '>') {
		add_token(match('>') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
	}
	else if (c == '/') {
		// Case 1: A comment
		if (match('/')) {
			// A comment goes until the end of the line, so we can advance accordingly
			while (peek() != '\n' && !is_at_end()) { advance(); }
		}
		// Case 2: A block comment
		else if (match('*')) {
			block_comment();
		}
		// Case 3: Just a slash
		else {
			add_token(TokenType::SLASH);
		}
	}
	/*
	The following case cover nuisance text formatting characters
	*/
	else if (c == '\n') {
		line++;
	}
	/*
	The following cases are for literals
	*/
	else if (c == '"') {
		string();
	}
	else if (is_digit(c)) {
		number();
	}
	else if (is_alpha(c)) {
		identifier();
	}
	else if (" ") {
		// Skip it, this statement is just here so that the else doesn't run in case of whitespace
	}
	else {
		error(line, "Unexpected character.");
	}
}


char lox::Scanner::advance() {
	return source.at(current++);
}

bool lox::Scanner::match(char expected) {
	if (is_at_end()) { return false; }
	if (source.at(current) != expected) { return false; }
	current++;
	return true;
}

char lox::Scanner::peek() {
	if (is_at_end()) { return 0; }
	return source.at(current);
}

char lox::Scanner::peek_next() {
	if (current + 1 >= source.length()) { return '\0'; }
	return source.at(current + 1);
}

void lox::Scanner::string() {
	// Lox supports multi-line strings, so if we see a \n inside the string literal we need to increment line
	while (peek() != '"' && !is_at_end()) {
		if (peek() == '\n') { line++; }
		advance();
	}

	if (is_at_end()) {
		error(line, "Unterminated string");
	}

	// The closing quote
	advance();

	// Trim surrounding quotes
	std::string value = source.substr(start + 1, current - 1 - (start + 1));
	
	// Note that lox does not have escape sequences, so we are now ready to add the token
	// If it did support escape sequences, un-escaping those escape sequences would be needed
	add_token(TokenType::STRING, value);
}

bool lox::Scanner::is_digit(char c) {
	return c >= '0' && c <= '9';
}

bool lox::Scanner::is_alpha(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool lox::Scanner::is_alphanumeric(char c) {
	return is_alpha(c) || is_digit(c);
}

void lox::Scanner::number() {
	while (is_digit(peek())) { advance(); }
	// Check if the number has a decimal point and consume it if it does
	if (peek() == '.' && is_digit(peek_next())) {
		advance();
		while (is_digit(peek())) { advance(); }
	}

	add_token(TokenType::NUMBER, stod(source.substr(start, current - start)));
}

void lox::Scanner::identifier() {
	while (is_alphanumeric(peek())) { advance(); }
	
	std::string text = source.substr(start, current - start);
	TokenType type = str_literal_to_lox_keywords[text];
	if (type == NULL) { type = IDENTIFIER; }
	add_token(type);
}

void lox::Scanner::block_comment() {
	while (!is_at_end()) {
		char c = advance();

		// Lox block comments can span over multiple lines
		if (c == '\n') { line++; }

		if (c == '*' && match('/')) { return; }
	}

	error(line, "Could not find end of block comment");
}

void lox::Scanner::add_token(TokenType type) {
	add_token(type, NULL);
}

void lox::Scanner::add_token(TokenType type, lox_literal_t literal) {
	std::string text = source.substr(start, current - start);
	tokens.push_back(Token(type, text, literal, line));
}

std::vector<lox::Token> lox::Scanner::scan_tokens() {
	while (!is_at_end()) {
		start = current;
		scan_token();
	}

	tokens.push_back(Token(TokenType::_EOF, "", NULL, line));
	return tokens;
}