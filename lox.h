#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include <vector>

#include "scanner.h"
#include "token.h"

class Lox {
private:
	bool had_error;

public:
	Lox();
	
	void run_file(std::string filepath); 
	void run_prompt();
	void lox_main(int argc, const char* argv[]);
	void run(std::string source);
};