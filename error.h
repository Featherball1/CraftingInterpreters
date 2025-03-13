#pragma once
#include <iostream>
#include <string>

namespace lox {
	void error(int line, std::string message);
	void report(int line, std::string where, std::string message);
}