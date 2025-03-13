#include "error.h"

void error(int line, std::string message) {
	report(line, "", message);
}

void report(int line, std::string where, std::string message) {
	std::cout << "[line " << line << "] Error " << where << ": " << message << std::endl;
}