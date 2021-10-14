#pragma once
#include <iostream>

enum class token_type 
{ 
	null, 
	text, 
	number, 
	op, 
	opening_parenthesis, 
	closing_parenthesis, 
	arg_separator
};

void print_token_type(const token_type& type);
