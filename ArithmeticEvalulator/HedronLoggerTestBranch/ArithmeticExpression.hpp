#pragma once
#include <boost/regex/v4/regex.hpp>
#include "ArithmeticToken.hpp"

class ArithmeticExpression
{
public:
	static boost::regex is_number_regex;
	static boost::smatch match_info;
	static std::vector<char> char_operator;
	static std::vector<std::vector<std::string>> text_operator_dictionary;

	static void normalize_infix(std::string& infix);
	static std::vector<ArithmeticToken> tokenize_infix(std::string& infix);
	static std::vector<ArithmeticToken> infix_to_postfix(std::string& infix);
	static double evaluate(std::string infix);
};