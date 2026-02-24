/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:42:14 by ghambrec          #+#    #+#             */
/*   Updated: 2026/02/24 14:50:58 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <fstream>
#include <stdexcept>

inline const std::string DB_FILE{"data/data.csv"};
inline const std::regex REGEX_LINE{R"(^(\d{4}-\d{2}-\d{2})\s\|\s(\d{1,4}(?:\.\d*)?)f?$)"};

class BitcoinExchange
{
	private:
		std::map<std::string, double> btc_;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		// member functions
		void loadDatabase(const std::string& file);
		double find(std::string& date, int i) const;
};
