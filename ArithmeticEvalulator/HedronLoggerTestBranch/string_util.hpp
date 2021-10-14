#pragma once
#include <boost/regex/v4/regex.hpp>
#include "ArithmeticExpression.hpp"

namespace string_util
{
	bool is_number(std::string str)
	{
		return boost::regex_match(str, ArithmeticExpression::match_info, ArithmeticExpression::is_number_regex);
	}

	bool is_digit(char c)
	{
		return c >= '0' && c <= '9';
	}

	bool is_number_char(char c)
	{
		return (c >= '0' && c <= '9') || c == '.';
	}

	int is_letter(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}

	int is_text_operator(std::string str)
	{
		for (unsigned i = 0; i < ArithmeticExpression::text_operator_dictionary.size(); i++)
		{
			for (unsigned j = 0; j < ArithmeticExpression::text_operator_dictionary[i].size(); j++)
			{
				if (ArithmeticExpression::text_operator_dictionary[i][j] == str)
				{
					return i + 1;
				}
			}
		}
		return 0;
	}

	int is_operator(char c)
	{
		for (unsigned i = 0; i < ArithmeticExpression::char_operator.size(); i++)
		{
			if (c == ArithmeticExpression::char_operator[i]) return 1;
		}
		return 0;
	}

	void to_lower_case(std::string& str)
	{
		for (unsigned i = 0; i < str.size(); i++)
		{
			if (str[i] >= 'A' && str[i] < 'Z')
			{
				str[i] += 32;
			}
		}
	}
	int is_parenthesis(char c)
	{
		return c == '(' || c == ')';
	}
	int arity(std::string str)
	{
		int is_t_operator = is_text_operator(str);
		if (is_t_operator != 0)
			return is_t_operator;
		if (is_operator(str[0]))
			return 1;
		return 0;
	}

	int precedence(std::string& str)
	{
		if (str == "^") return 5;
		else if (str == "*" || str == "/" || str == "%") return 4;
		else if (str == "+" || str == "-") return 3;
		else if (str == "&") return 2;
		else if (str == "|") return 1;
		return 0;
	}
}