#include "lox.h"

Lox::Lox() : had_error(false) {}

void Lox::lox_main(int argc, const char* argv[]) {
	/*
	if (args.length > 1) {
		There were too many arguments
	}
	else if (args.length == 1) {
		One file was provided, interpret it
	} 
	else {
		No files were provided, we are in run prompt mode
	}
	*/

	if (argc > 2) {
		std::cout << "Usage: lox [script]" << std::endl;
		exit(2);
	}
	else if (argc == 2) {
		std::cout << "lox_main: running file " << argv[1] << std::endl;
		run_file(argv[1]);
	}
	else {
		std::cout << "lox_main: running prompt" << std::endl;
		run_prompt();
	}
}

void Lox::run_file(std::string filepath) {
	if (had_error) { exit(2); }

	std::ifstream t(filepath);
	std::stringstream input_buffer;
	input_buffer << t.rdbuf();

	std::cout << input_buffer.str() << std::endl;
	
	Scanner scanner(input_buffer.str());

	std::vector<Token> tokens = scanner.scan_tokens();
	for (auto token : tokens) {
		std::cout << "Token " << token.to_string() << ", " << std::endl;
	}
}

void Lox::run_prompt() {
	while (true) {
		// Reset error flag to avoid killing the session if user makes a mistake
		had_error = false;

		std::string input_buffer;
		std::cout << "(lox) > ";
		getline(std::cin, input_buffer);
		std::cout << "You entered " << input_buffer << std::endl;

		if (input_buffer == "exit()") {
			break;
		}

		Scanner scanner(input_buffer);
		std::vector<Token> tokens = scanner.scan_tokens();
		for (auto token : tokens) {
			std::cout << "Token " << token.to_string() << ", " << std::endl;
		}
	}
}

void Lox::run(std::string source) {

}