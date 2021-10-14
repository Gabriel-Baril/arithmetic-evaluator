#include "ArithmeticExpression.hpp"

std::vector<std::string> process_script()
{
	std::vector<std::string> script;
	std::string current_line;
	bool is_valid;
	do
	{
		std::getline(std::cin, current_line);
		is_valid = current_line == "START SCRIPT";
		if (!is_valid)
		{
			std::cout << "INVALID\n";
		}
	} while (!is_valid);
	do
	{
		std::getline(std::cin, current_line);
		is_valid = current_line == "END SCRIPT";
		if (!is_valid)
		{
			script.push_back(current_line);
		}
	} while (!is_valid);
	return script;
}

struct LineData
{
	std::vector<std::string> tokens;
};

std::vector<char> separators = {0x20, '=', '"', '(', ',', ')'};

LineData tokenize_line(std::string str)
{
	LineData output;
	std::string current_token;
	for (unsigned i = 0;i < str.size();i++)
	{
		bool is_separator = false;
		for (unsigned j = 0;j < separators.size();j++)
		{
			if (str[i] == separators[j])
			{
				is_separator = true;
				break;
			}
		}
		if (is_separator)
		{
			if (!current_token.empty())
				output.tokens.push_back(current_token);
			output.tokens.push_back(std::string(1, str[i]));
			current_token.clear();
		}
		else
		{
			current_token.push_back(str[i]);
		}
	}
	output.tokens.push_back(current_token);
	return output;
}

int main()
{
	/*
	auto arr = process_script();
	for (unsigned i = 0;i < arr.size();i++)
	{
		auto output = tokenize_line(arr[i]);
		for (unsigned j = 0;j < output.tokens.size(); j++)
		{
			std::cout << output.tokens[j] << "\n";
		}
	}
	system("cd C:/Users/Gabriel/Desktop"
			"&& copy NUL test.txt"
			"&& echo bonjour > test.txt");
	*/




	// -9-cos(-5)
	std::string arithm_expression = "";// -4+5*(-12+5*6)-(+118-5)-4*-6+3*-73+(-9+6-7*-3) + 30^2+sqrt(-23+floor(27+3*51)+467)/2 + 3^2+sqrt(5+floor(5+3*7)+4)/2

	while (true)
	{
		std::getline(std::cin, arithm_expression);
		try
		{
			std::cout << ArithmeticExpression::evaluate(arithm_expression) << '\n' << '\n';
		}
		catch (std::exception& e)
		{
			std::cout << "INVALID ARITHMETIC EXPRESSION --> " << e.what() << std::endl;
		}
	}

	

	return 0;
}