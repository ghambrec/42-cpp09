/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:42:18 by ghambrec          #+#    #+#             */
/*   Updated: 2026/02/24 15:26:25 by ghambrec         ###   ########.fr       */
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

void process_line(std::string& date, float value, BitcoinExchange& btc_db, int i)
{
	double btc_amount = btc_db.find(date, i);
	double result = static_cast<double>(value) * btc_amount;

	std::cout << date << " => " << value << " = " << result << std::endl;
}

void parse_and_process_line(std::string& line, int i, BitcoinExchange& btc_db)
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

	process_line(date, value, btc_db, i);
}

void process_input_file(char *argv, BitcoinExchange& btc_db)
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
			parse_and_process_line(line, i, btc_db);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	if (i == 0)
		throw std::runtime_error("Error: Empty file!");
}

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		std::cerr << "Error: Wrong usage! Usage: ./btc [inputfile]\n";
		return (1);
	}

	BitcoinExchange btc_db;
	try
	{
		btc_db.loadDatabase(DB_FILE);
		process_input_file(argv[1], btc_db);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
