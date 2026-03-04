/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:12:36 by ghambrec          #+#    #+#             */
/*   Updated: 2026/03/04 12:52:30 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void fjalgo(std::vector<int>& v, size_t pair_size)
{
	if ((v.size() / pair_size) < 2)
		return ;
	
	// step 1 - build and sort pairs
	size_t count_elements = v.size() / pair_size;
	size_t count_pairs = count_elements / 2;	
	for (size_t pair = 0; pair < count_pairs; pair++)
	{
		size_t start_left = (2 * pair) * pair_size;
		size_t start_right = (2 * pair + 1) * pair_size;
		size_t key_left = start_right - 1;
		size_t key_right = start_right + pair_size - 1;

		if (v[key_left] > v[key_right]) // vergleich
		{
			for (size_t i = 0; i < pair_size; i++)
			{
				std::swap(v[start_left + i], v[start_right + i]);
			}
		}
	}

	// // printing for debug
	// size_t pair = 0;
	// size_t start_left = (2 * pair) * pair_size;
	// size_t start_right = (2 * pair + 1) * pair_size;
	// size_t key_left = start_right - 1;
	// size_t key_right = start_right + pair_size - 1;
	// std::cout << "pairsize: " << pair_size << std::endl;
	// std::cout << "- start l/f: " << start_left << "/" << start_right << std::endl;
	// std::cout << "- key l/f:   " << key_left << "/" << key_right << std::endl;
	// std::cout << "- elements: " << count_elements << "; pairs: " << count_pairs << std::endl;
	std::cout << "- after sorting pairs ";
	print_vector(v);
	
	fjalgo(v, pair_size * 2);

	// step 2 - build main and pend
	std::vector<int> main;
	std::vector<int> pend;

	for (size_t pair = 0; pair < count_pairs; pair++)
	{
		size_t start_left = (2 * pair) * pair_size;
		size_t start_right = (2 * pair + 1) * pair_size;

		if (pair == 0) // b1 kopieren
			main.insert(main.end(), v.begin() + start_left, v.begin() + start_left + pair_size);
		else
			pend.insert(pend.end(), v.begin() + start_left, v.begin() + start_left + pair_size);

		// restlichen a's kopieren
		main.insert(main.end(), v.begin() + start_right, v.begin() + start_right + pair_size);
	}
	// ggf. unpaired element mit in pend aufnehmen
	if (count_elements % 2 == 1)
	{
		size_t start_missing = (count_elements - 1) * pair_size;
		pend.insert(pend.end(), v.begin() + start_missing, v.begin() + start_missing + pair_size);
	}
	

	std::cout << "pairsize: " << pair_size << std::endl;
	std::cout << "- elements: " << count_elements << "; pairs: " << count_pairs << std::endl;
	std::cout << "- mainchain ";
	print_vector(main);
	std::cout << "- pendchain ";
	print_vector(pend);
	
		
}
