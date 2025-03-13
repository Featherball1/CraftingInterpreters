#pragma once
#include <string>
#include <variant>

/*
This std::variant contains all the types that a lox literal can be
This allows us to refer to a lox literal in general without getting more granular
about the type information
*/

typedef std::variant<
	int,
	bool,
	double,
	std::string
> lox_literal_t;