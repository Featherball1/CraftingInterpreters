#include <iostream>
#include "lox.h"

#include "token.h"

int main(int argc, const char* argv[]) {
	std::cout << "Hello World" << std::endl;
	
	std::cout << "argc: " << argc << ", argv: " << argv[1] << std::endl;

	lox::Lox lox;
	lox.lox_main(argc, argv);

	return 0;
}