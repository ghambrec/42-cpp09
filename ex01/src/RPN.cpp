/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:38:04 by ghambrec          #+#    #+#             */
/*   Updated: 2026/02/25 01:14:47 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static bool check_value(std::string& value)
{
	static std::regex REGEX{R"(^\d?\+?-?\/?\*?$)"};

	std::smatch match;
	if (!std::regex_match(value, match, REGEX))
		return (false);
	return (true);
}

static bool is_operator(std::string& value)
{
	if (value == "+" || value == "-" || value == "/" || value == "*")
		return (true);
	return (false);
}

void rpn(char *str)
{
	std::stack<int>		stack;
	std::istringstream	stream(str);
	std::string			value;

	while (stream >> value)
	{
		if (!check_value(value))
			throw std::runtime_error("Error: Invalid value '" + value + "'");
		
		if (is_operator(value))
		{
			if (stack.size() >= 2)
			{
				int b = stack.top();
				stack.pop();
				int a = stack.top();
				stack.pop();

				int result;
				if (value == "+")
					result = a + b;
				if (value == "-")
					result = a - b;
				if (value == "/")
					result = a / b;
				if (value == "*")
					result = a * b;
				stack.push(result);
			}
			else
				throw std::runtime_error("Error: Not enough values in stack for operator '" + value + "'");
		}
		else
		{
			int number = std::stoi(value);
			stack.push(number);
		}
	}
	if (stack.size() == 1)
		std::cout << stack.top() << std::endl;
	else
		throw std::runtime_error("Error: More than one number in the stack at the end of the calculation");
}
