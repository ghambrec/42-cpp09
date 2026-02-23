/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:42:18 by ghambrec          #+#    #+#             */
/*   Updated: 2026/02/23 13:28:54 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void read_input_file(char *argv)
{
	std::ifstream input_file(argv);
	if (!input_file)
		throw std::runtime_error("Error: Couldn't open input file!");
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
		read_input_file(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	


}
