/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:42:18 by ghambrec          #+#    #+#             */
/*   Updated: 2026/02/24 13:37:53 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void parse_header(std::string& header, int i)
{
	if (header != "date | value")
		throw std::runtime_error("Error at line " + std::to_string(i) + ": Invalid header!");
}

bool check_date(std::string& date)
{
	int year = std::stoi(date.substr(0,4));
	int month = std::stoi(date.substr(5,2));
	int day = std::stoi(date.substr(8,2));

	if (year < 1900 || month == 00 || month > 12 || day == 00)
		return (false);

	int max_days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		max_days[1] = 29;

	if (day > max_days[month - 1])
		return (false);

	return (true);
}

bool check_value(float value)
{
	if (value > 1000)
		return (false);
	return (true);
}

void parse_line(std::string& line, int i)
{
	std::smatch match;
	if (!std::regex_match(line, match, REGEX_LINE))
		throw std::runtime_error("Error at line " + std::to_string(i) + ": Invalid line format!");

	std::string date = match[1];
	float value = std::stof(match[2]);

	if (!check_date(date))
		throw std::runtime_error("Error at line " + std::to_string(i) + ": Invalid date!");
	
	if (!check_value(value))
		throw std::runtime_error("Error at line " + std::to_string(i) + ": Invalid value!");
}

void process_input_file(char *argv)
{
	std::ifstream input_file(argv);
	if (!input_file)
		throw std::runtime_error("Error: Couldn't open input file!");
	
	int i = 0;
	std::string line;
	while (std::getline(input_file, line))
	{
		i++;
		if (i == 1)
		{
			parse_header(line, i);
			continue;
		}
		try
		{
			std::cout << "[" << i << "] "; // zum testen
			parse_line(line, i);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		break; // zum testen nur eine zeile nehmen
	}
}

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		std::cerr << "Error: Wrong usage! Usage: ./btc [inputfile]\n";
		return (1);
	}

	BitcoinExchange btc;
	try
	{
		btc.loadDatabase(DB_FILE);
		process_input_file(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	


}
