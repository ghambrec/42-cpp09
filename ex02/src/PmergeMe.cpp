/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:12:36 by ghambrec          #+#    #+#             */
/*   Updated: 2026/03/04 11:11:32 by ghambrec         ###   ########.fr       */
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

		if (v[key_left] > v[key_right])
		{
			for (size_t i = 0; i < pair_size; i++)
			{
				std::swap(v[start_left + i], v[start_right + i]);
			}
		}
	}

	// printing for debug
	std::cout << "pairsize: " << pair_size << std::endl;
	std::cout << "- elements: " << count_elements << "; pairs: " << count_pairs << std::endl;
	std::cout << "- after sorting ";
	print_vector(v);
	
	fjalgo(v, pair_size * 2);
		
}