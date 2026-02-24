/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:42:16 by ghambrec          #+#    #+#             */
/*   Updated: 2026/02/24 15:04:34 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() { std::cout << "CONSTRUCTOR CALLED\n"; }

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
	:	btc_(other.btc_)
{ std::cout << "copy CONSTRUCTOR CALLED\n"; }

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	 std::cout << "assignment CONSTRUCTOR CALLED\n"; 
	if (this != &other)
		btc_ = other.btc_;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& file)
{
	std::ifstream dbfile(file);
	if (!dbfile)
		throw std::runtime_error("Error: Couldn't open database file!");
	
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

double BitcoinExchange::find(std::string& date, int i) const
{
	auto it = btc_.find(date);

	if (it == btc_.end())
	{
		if (date < btc_.begin()->first)
			throw std::runtime_error("Error at line " + std::to_string(i) + ": Date too old for data!");

		it--;
		while (date < it->first)
			it--;
	}
	return (it->second);	
}
