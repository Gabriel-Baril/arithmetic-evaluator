#include "TokenType.hpp"

void print_token_type(const token_type& type)
{
	switch (type)
	{
	case token_type::null:
		std::cout << "NULL" << std::endl;
		break;
	case token_type::text:
		std::cout << "TEXT" << std::endl;
		break;
	case token_type::number:
		std::cout << "NUMBER" << std::endl;
		break;
	case token_type::op:
		std::cout << "OPERATOR" << std::endl;
		break;
	case token_type::opening_parenthesis:
		std::cout << "OPENING_PARENTHESIS" << std::endl;
		break;
	case token_type::closing_parenthesis:
		std::cout << "CLOSING_PARENTHESIS" << std::endl;
		break;
	case token_type::arg_separator:
		std::cout << "ARGUMENT_PARENTHESIS" << std::endl;
		break;
	default:
		std::cout << "UNDEFINED" << std::endl;
	}
}
