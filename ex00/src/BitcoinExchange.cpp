/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:42:16 by ghambrec          #+#    #+#             */
/*   Updated: 2026/02/23 13:13:34 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
	:	btc_(other.btc_)
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		btc_ = other.btc_;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& file)
{
	std::ifstream dbfile(file);
	if (!dbfile)
	{
		std::cerr << "Error: Couldn't open Database file!";
		exit(1);
	}
	
	std::string line;
	while (std::getline(dbfile, line))
	{
		if (line == "date,exchange_rate")
			continue;

		std::string date = line.substr(0,10);
		std::string value_str = line.substr(11, line.length() - 11);
		double value = std::stod(value_str);
		btc_[date] = value;
	}
}
