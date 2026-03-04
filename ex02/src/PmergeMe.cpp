/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:12:36 by ghambrec          #+#    #+#             */
/*   Updated: 2026/03/04 17:53:27 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void print_vector(const std::vector<size_t> &v)
{
	// print given numbers
	for (size_t n : v)
	{
		std::cout << n << " ";
	}
	std::cout << "\n";
}

static std::vector<size_t> get_insertion_order(size_t pend_count)
{
	std::vector<size_t> insertion_order;
	insertion_order.reserve(pend_count);

	size_t prev_jacob = 1; // b1 (is schon in main drin)
	size_t curr_jacob = 3; // b2, b3 (in pend)

	while (insertion_order.size() < pend_count)
	{
		size_t start = std::min(curr_jacob, pend_count + 1);
		for (size_t b_idx = start; b_idx > prev_jacob; b_idx--)
		{
			size_t pend_idx = b_idx - 2;
			if (pend_idx < pend_count)
				insertion_order.push_back(pend_idx);
		}
		size_t next_jacob = curr_jacob + 2 * prev_jacob;
		prev_jacob = curr_jacob;
		curr_jacob = next_jacob;
	}
	return (insertion_order);
}

void fjalgo(std::vector<int> &v, size_t element_size)
{
	if ((v.size() / element_size) < 2)
		return;

	// step 1 - build and sort pairs
	size_t count_elements = v.size() / element_size;
	size_t count_pairs = count_elements / 2;
	for (size_t pair = 0; pair < count_pairs; pair++)
	{
		size_t start_left = (2 * pair) * element_size;
		size_t start_right = (2 * pair + 1) * element_size;
		size_t key_left = start_right - 1;
		size_t key_right = start_right + element_size - 1;

		if (v[key_left] > v[key_right]) // vergleich
		{
			for (size_t i = 0; i < element_size; i++)
			{
				std::swap(v[start_left + i], v[start_right + i]);
			}
		}
	}

	// // printing for debug
	// size_t pair = 0;
	// size_t start_left = (2 * pair) * element_size;
	// size_t start_right = (2 * pair + 1) * element_size;
	// size_t key_left = start_right - 1;
	// size_t key_right = start_right + element_size - 1;
	// std::cout << "pairsize: " << element_size << std::endl;
	// std::cout << "- start l/f: " << start_left << "/" << start_right << std::endl;
	// std::cout << "- key l/f:   " << key_left << "/" << key_right << std::endl;
	// std::cout << "- elements: " << count_elements << "; pairs: " << count_pairs << std::endl;
	// std::cout << "- after sorting pairs ";
	// print_vector(v);

	fjalgo(v, element_size * 2);




	
	// step 2 - build main and pend
	std::vector<int> main;
	std::vector<int> pend;

	for (size_t pair = 0; pair < count_pairs; pair++)
	{
		size_t start_left = (2 * pair) * element_size;
		size_t start_right = (2 * pair + 1) * element_size;

		if (pair == 0) // b1 kopieren
			main.insert(main.end(), v.begin() + start_left, v.begin() + start_left + element_size);
		else
			pend.insert(pend.end(), v.begin() + start_left, v.begin() + start_left + element_size);

		// restlichen a's kopieren
		main.insert(main.end(), v.begin() + start_right, v.begin() + start_right + element_size);
	}
	// ggf. unpaired element mit in pend aufnehmen
	if (count_elements % 2 == 1)
	{
		size_t start_missing = (count_elements - 1) * element_size;
		pend.insert(pend.end(), v.begin() + start_missing, v.begin() + start_missing + element_size);
	}

	// std::vector<int> rest;
	// size_t anzahl_rest = v.size() - ((element_size * 2) * count_pairs);
	// size_t numbers_used = element_size * 2  * count_pairs;
	// if (anzahl_rest > 0)
	// 	rest.insert(rest.begin(), v.end() - anzahl_rest, v.end());

	if (element_size == 4)
	{
		// print for debugging
		std::cout << "ELEMENT SIZE: " << element_size << std::endl;
		// std::cout << "- restsize: " << anzahl_rest << std::endl;
		// std::cout << "- usednumb: " << numbers_used << std::endl;
		// std::cout << "- ";
		// print_vector(v);
		std::cout << "- elements: " << count_elements << "; pairs: " << count_pairs << std::endl;
		std::cout << "- mainchain ";
		print_vector(main);
		std::cout << "- pendchain ";
		print_vector(pend);
		// std::cout << "- restchain ";
		// print_vector(rest);
	}









	// step 3 - insert pend into main

	// nur noetig wenn ein pend da ist
	size_t pend_count = pend.size() / element_size;
	if (pend_count > 0)
	{
		std::vector<size_t> insertion_order = get_insertion_order(pend_count);


		if (element_size == 4)
		{
			std::cout << "- >> insertfolge: ";
			print_vector(insertion_order);
		}

		// jedes pent element bearbeiten
		for (size_t i = 0; i < insertion_order.size(); i++)
		{
			size_t pend_idx = insertion_order[i];

			// get the current pend element
			std::vector<int> cur_pend_element(pend.begin() + pend_idx * element_size, pend.begin() + (pend_idx + 1) * element_size);
			int key = cur_pend_element[element_size - 1];

			if (element_size == 4)
			{
				std::cout << "- ELEM INSERT: ";
				print_vector(cur_pend_element);
			}


			// ### BOUND BERECHNEN HIER NOCH EINBAUEN ###
			size_t search_end = main.size() / element_size; // ganze main chain durchsuchen, da bound fehlt


			// binary search for insert position
			size_t lo = 0;
			size_t hi = search_end;
			while (lo < hi)
			{
				size_t mid_element = lo + (hi - lo) / 2;
				int mid_key = main[mid_element * element_size + element_size - 1];
				if (mid_key < key) // vergleich
					lo = mid_element + 1;
				else
					hi = mid_element;
			}

			// insert pend element in main chain
			main.insert(main.begin() + lo * element_size, cur_pend_element.begin(), cur_pend_element.end());
		}
	}

	// copy sorted main chain back to the original chain
	for (size_t i = 0; i < main.size(); i++)
		v[i] = main[i];


	if (element_size == 4)
	{
		std::cout << "- after insert ";
		print_vector(v);
	}
}
