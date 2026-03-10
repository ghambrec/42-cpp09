/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:12:11 by ghambrec          #+#    #+#             */
/*   Updated: 2026/03/10 10:30:45 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static int parse_argument(const std::string& str)
{
	static std::regex REGEX{R"(^[+-]?\d+$)"};
	std::smatch match;
	if (!std::regex_match(str, match, REGEX))
		throw std::runtime_error("Error: Detected a non number value!");
	
	long long ln = std::stoll(str);
	if (ln <= 0)
		throw std::runtime_error("Error: Detected number equal or smaller 0");
	if (ln > std::numeric_limits<int>::max())
		throw std::runtime_error("Error: Detected number bigger than INT_MAX");
	return (static_cast<int>(ln));
}

void print_vector(const std::vector<int>& v)
{
	std::cout << "Numbers: ";
	for (int n : v)
	{
		std::cout << n << " ";	
	}
	std::cout << "\n";
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Error: Minimum 2 arguments needed!\n";
		return (1);
	}

	// create vector with int numbers
	std::vector<int> v;
	int i = 1;
	try
	{
		while (argv[i])
		{
			v.push_back(parse_argument(argv[i]));
			i++;
		}

		// print_vector(v);

		// algo
		fj_algo(v, 1);
		// fjalgo(v, 4);
	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


}
