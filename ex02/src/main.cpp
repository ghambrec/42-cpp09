/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:12:11 by ghambrec          #+#    #+#             */
/*   Updated: 2026/03/10 12:13:33 by ghambrec         ###   ########.fr       */
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

static void print_vector(const std::vector<int>& v)
{
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

	std::vector<int> v;
	int i = 1;
	try
	{
		while (argv[i])
		{
			v.push_back(parse_argument(argv[i]));
			i++;
		}
		std::cout << "Before: ";
		print_vector(v);
	
		auto start = std::chrono::steady_clock::now();
		fj_algo(v, 1);
		auto end = std::chrono::steady_clock::now();
		auto dauer_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		auto dauer_us = dauer_ns / 1000.0;
	
		std::cout << "After:  ";
		print_vector(v);
		std::cout	<< "Time to process a range of "
					<< v.size()
					<< " elements with std::vector<int> : "
					<< std::fixed << std::setprecision(5)
					<< dauer_us
					<< " us\n";
	
		if (!std::is_sorted(v.begin(), v.end()))
			throw std::runtime_error("Error: Vector is not sorted!");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


}
