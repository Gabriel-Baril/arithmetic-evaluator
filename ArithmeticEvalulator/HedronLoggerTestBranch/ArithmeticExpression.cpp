#include <stack>
#include <cmath>
#include "ArithmeticExpression.hpp"
#include "string_util.hpp"

boost::regex ArithmeticExpression::is_number_regex = boost::regex("-?[0-9]+(?:[.,][0-9]+)?");
boost::smatch ArithmeticExpression::match_info = boost::smatch();
std::vector<char> ArithmeticExpression::char_operator = { '+', '-', '*', '/', '^', '%', '|', '&' };
std::vector<std::vector<std::string>> ArithmeticExpression::text_operator_dictionary =
{
	{
		"abs", "acos", "acosh", "asin", "asinh", "atan", "atanh",
		"cbrt", "ceil", "cos", "cosh", "erf", "erfc", "exp", "exp2",
		"expm1", "floor", "lgamma", "log", "log1p", "log2", "logb", "log10", "nearbyint",
		"round", "sin", "sinh", "sqrt", "tan", "tanh", "tgamma", "trunc", "comp", "neg" // 1 arg operator
	},
	{
		"atan2", "pow", "copysign", "dim", "max", "min", "hypot", "ldexp",
		"remainder", "nextafter", "add", "sub", "mult", "div",
		"scalbn", "or", "and", "xor", "mod" // 2 arg operator
	},
	{
		"ma"
		// 3 arg operator
	}
	// ...
};

void ArithmeticExpression::normalize_infix(std::string& infix)
{
	//infix = boost::regex_replace(infix, boost::regex(","), ".", boost::format_all);
	infix = boost::regex_replace(infix, boost::regex("--"), "+", boost::format_all);
	infix = boost::regex_replace(infix, boost::regex("[+]{2,}"), "+", boost::format_all);
	infix.insert(0, "(");
	infix.append(")");

	if (boost::regex_search(infix, ArithmeticExpression::match_info, boost::regex("(?:[\-\*\/\+\|\&\^][\*\/\|\&\^]|[\+][\-][\*\/\+\|\&\^])"))) // operator combinaison
	{
		std::string error_msg = "INVALID OPERATOR COMBINAISON ---> AT \"";
		throw std::exception(error_msg.append(ArithmeticExpression::match_info[0] + "\"").c_str());
	}

	if (infix[0] == '-' || infix[0] == '+') infix.insert(0, "0");
	for (unsigned i = infix.size() - 2; i > 0; i--)
	{
		if ((infix[i] == '-' || infix[i] == '+'))
		{
			if (infix[i - 1] == '(' || infix[i - 1] == ',')
			{
				infix.insert(i, "0");
			}
			else if (string_util::is_operator(infix[i - 1]))
			{
				infix.insert(i, "0");
				infix.insert(i, "(");
				int j = i + 3;
				while ((infix[j] >= '0' && infix[j] <= '9') || infix[j] == '.')
				{
					j++;
				}
				infix.insert(j, ")");
			}
		}
	}
}

std::vector<ArithmeticToken> ArithmeticExpression::tokenize_infix(std::string& infix)
{
	std::vector<ArithmeticToken> output;
	ArithmeticToken current_token;
	token_type type = token_type::null;
	auto manage_current_token = [](const token_type& token_type_match, ArithmeticToken& current_token, char& current_char, std::vector<ArithmeticToken>& output)
	{
		if (current_token.type != token_type_match)
		{
			if (!current_token.value.empty())
			{
				output.push_back(current_token);
				current_token.value.clear();
			}
			current_token.type = token_type_match;
		}
		current_token.value.push_back(current_char);
	};
	
	infix.erase(std::remove_if(infix.begin(), infix.end(), ::isspace), infix.end());
	
	if (string_util::is_number(infix))
	{
		output.push_back({ infix, token_type::number });
		return output;
	}
	ArithmeticExpression::normalize_infix(infix);
	for (unsigned i = 0; i < infix.size(); i++)
	{
		if (string_util::is_letter(infix[i]))			manage_current_token(token_type::text, current_token, infix[i], output);
		else if (string_util::is_number_char(infix[i]))	manage_current_token(token_type::number, current_token, infix[i], output);
		else if (string_util::is_operator(infix[i]))		manage_current_token(token_type::op, current_token, infix[i], output);
		else if (infix[i] == '(')
		{
			output.push_back(current_token);
			current_token.value.clear();
			current_token.type = token_type::opening_parenthesis;
			current_token.value.push_back('(');
			output.push_back(current_token);
			current_token.value.clear();
		}
		else if (infix[i] == ')')
		{
			output.push_back(current_token);
			current_token.value.clear();
			current_token.type = token_type::closing_parenthesis;
			current_token.value.push_back(')');
			output.push_back(current_token);
			current_token.value.clear();
		}
		else if (infix[i] == ',')
		{
			output.push_back(current_token);
			current_token.value.clear();
			current_token.type = token_type::arg_separator;
			current_token.value.push_back(',');
			output.push_back(current_token);
			current_token.value.clear();
		}
		else
		{
			throw std::exception(std::string("UNEXPECTED CHARACTER --> ").append(std::string(1, infix[i])).c_str());
		}
	}
	output.push_back(current_token);

	for (unsigned i = 0; i < output.size(); i++)
	{
		if (output.at(i).type == token_type::text)
		{
			string_util::to_lower_case(output.at(i).value);
		}
	}

	for (int i = output.size() - 1; i >= 0; i--)
	{
		if (output.at(i).type == token_type::text)
		{
			if (string_util::is_text_operator(output.at(i).value) == 0)
			{
				//std::string error_msg = std::string("UNDEFINED OPERATOR --> ").append(output.at(i).value);
				throw std::exception(std::string("UNDEFINED OPERATOR --> ").append(output.at(i).value).c_str());
			}
			std::swap(output.at(i), output.at(i + 1));
			i++; // Must skip the next token because it is the one that we just check
		}
		else if (output.at(i).value.empty())
		{
			output.erase(output.begin() + i);
		}
	}
	return output;
}

std::vector<ArithmeticToken> ArithmeticExpression::infix_to_postfix(std::string& infix)

{
	std::vector<ArithmeticToken> tokens = ArithmeticExpression::tokenize_infix(infix);
	std::vector<ArithmeticToken> postfix;
	std::stack<ArithmeticToken> op_stack;
	ArithmeticToken op;

	for (unsigned i = 0; i < tokens.size(); i++)
	{
		std::cout << tokens[i].value << " ";
	}
	std::cout << std::endl;

	for (ArithmeticToken & tok : tokens)
	{
		if (tok.type == token_type::opening_parenthesis)
		{
			op_stack.push(tok);
		}
		else if (tok.type == token_type::number)
		{
			postfix.push_back(tok);
		}
		else if (tok.type == token_type::op || tok.type == token_type::text)
		{
			op = op_stack.top();
			op_stack.pop();
			while (op.type != token_type::opening_parenthesis && string_util::precedence(op.value) >= string_util::precedence(tok.value))
			{
				postfix.push_back(op);
				op = op_stack.top();
				op_stack.pop();
			}
			op_stack.push(op);
			op_stack.push(tok);
		}
		else if (tok.type == token_type::closing_parenthesis)
		{
			op = op_stack.top();
			op_stack.pop();
			while (op.type != token_type::opening_parenthesis)
			{
				postfix.push_back(op);
				op = op_stack.top();
				op_stack.pop();
			}
		}
		else if (tok.type == token_type::arg_separator)
		{
			// ...
		}
	}
	for (auto tok : postfix)
	{
		std::cout << tok.value << " ";
	}

	std::cout << std::endl;
	return postfix;
}

double ArithmeticExpression::evaluate(std::string infix)
{
	if (infix.empty())
	{
		throw std::exception("EMPTY EXPRESSION");
	}

	std::vector<ArithmeticToken> postfix = ArithmeticExpression::infix_to_postfix(infix);

	std::stack<double> stack;
	double A;
	double B;
	double C;
	double val;

	for (unsigned i = 0; i < postfix.size(); i++)
	{
		ArithmeticToken& current = postfix[i];
		if (current.type == token_type::number)
		{
			stack.push(std::stod(current.value));
		}
		else if (current.type == token_type::text)
		{
			if (string_util::arity(current.value) == 1)
			{
				if (stack.empty()) throw std::exception("BUG");
				A = stack.top(); stack.pop();

				if (current.value == "abs") val = abs(A);
				else if (current.value == "acos") val = acos(A);
				else if (current.value == "acosh") val = acosh(A);
				else if (current.value == "asin") val = asin(A);
				else if (current.value == "asinh") val = asinh(A);
				else if (current.value == "atan") val = atan(A);
				else if (current.value == "atanh") val = atanh(A);
				else if (current.value == "cbrt") val = cbrt(A);
				else if (current.value == "ceil") val = ceil(A);
				else if (current.value == "cos") val = cos(A);
				else if (current.value == "cosh") val = cosh(A);
				else if (current.value == "erf") val = erf(A);
				else if (current.value == "erfc") val = erfc(A);
				else if (current.value == "exp") val = exp(A);
				else if (current.value == "exp2") val = exp2(A);
				else if (current.value == "expm1") val = expm1(A);
				else if (current.value == "floor") val = floor(A);
				else if (current.value == "lgamma") val = lgamma(A);
				else if (current.value == "log") val = log(A);
				else if (current.value == "log1p") val = log1p(A);
				else if (current.value == "log2") val = log2(A);
				else if (current.value == "logb") val = logb(A);
				else if (current.value == "log10") val = log10(A);
				else if (current.value == "nearbyint") val = nearbyint(A);
				else if (current.value == "round") val = round(A);
				else if (current.value == "sin") val = sin(A);
				else if (current.value == "sinh") val = sinh(A);
				else if (current.value == "sqrt") val = sqrt(A);
				else if (current.value == "tan") val = tan(A);
				else if (current.value == "tanh") val = tanh(A);
				else if (current.value == "tgamma") val = tgamma(A);
				else if (current.value == "trunc") val = trunc(A);
				else if (current.value == "comp") val = ~static_cast<int>(A);
				else if (current.value == "neg") val = -A;
			}
			else if (string_util::arity(current.value) == 2)
			{
				if (stack.empty()) throw std::exception("BUG");
				A = stack.top(); stack.pop();
				if (stack.empty()) throw std::exception("BUG");
				B = stack.top(); stack.pop();

				if (current.value == "add") val = B + A;
				else if (current.value == "sub") val = B - A;
				else if (current.value == "mult") val = B * A;
				else if (current.value == "div") val = B / A;
				else if (current.value == "atan2") val = atan2(B, A);
				else if (current.value == "pow") val = pow(B, A);
				else if (current.value == "copysign") val = copysign(B, A);
				else if (current.value == "dim") val = fdim(B, A);
				else if (current.value == "max") val = fmax(B, A);
				else if (current.value == "min") val = fmin(B, A);
				else if (current.value == "hypot") val = hypot(B, A);
				else if (current.value == "ldexp") val = ldexp(B, A);
				else if (current.value == "remainder") val = remainder(B, A);
				else if (current.value == "nextafter") val = nextafter(B, A);
				else if (current.value == "scalbn") val = scalbn(B, A);
				else if (current.value == "copysign") val = copysign(B, A);
				else if (current.value == "or") val = static_cast<int>(B) | static_cast<int>(A);
				else if (current.value == "and") val = static_cast<int>(B) & static_cast<int>(A);
				else if (current.value == "xor") val = static_cast<int>(B) ^ static_cast<int>(A);
				else if (current.value == "mod") val = fmod(B, A);
			}
			else if (string_util::arity(current.value) == 3)
			{
				if (stack.empty()) throw std::exception("BUG");
				A = stack.top(); stack.pop();
				if (stack.empty()) throw std::exception("BUG");
				B = stack.top(); stack.pop();
				if (stack.empty()) throw std::exception("BUG");
				C = stack.top(); stack.pop();

				if (current.value == "ma") val = fma(C, B, A);
			}
			stack.push(val);
		}
		else if (current.type == token_type::op)
		{
			if (stack.empty()) throw std::exception("BUG");
			A = stack.top(); stack.pop();
			if (stack.empty()) throw std::exception("BUG");
			B = stack.top(); stack.pop();

			if (current.value == "^") val = pow(B, A);
			else if (current.value == "*") val = B * A;
			else if (current.value == "/") val = B / A;
			else if (current.value == "%") val = fmod(B, A);
			else if (current.value == "+") val = B + A;
			else if (current.value == "-") val = B - A;
			else if (current.value == "&") val = static_cast<int>(B) & static_cast<int>(A);
			else if (current.value == "|") val = static_cast<int>(B) | static_cast<int>(A);
			stack.push(val);
		}
	}
	return stack.top();
}
