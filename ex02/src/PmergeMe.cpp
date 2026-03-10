/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:12:36 by ghambrec          #+#    #+#             */
/*   Updated: 2026/03/10 11:14:49 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static std::vector<size_t> get_insertion_order(size_t pend_count)
{
	std::vector<size_t> insertion_order;
	insertion_order.reserve(pend_count);

	size_t prev_jacob = 1;
	size_t curr_jacob = 3;

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

// STEP 1 - BUILD AND SORT PAIRS
// pair = [b,a]
// b = smaller value
// a = bigger value
static void fj_build_and_sort_pairs(std::vector<int>& v, size_t count_pairs, size_t element_size)
{
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
}

// STEP 2 - BUILD MAIN AND PEND CHAIN
// main: b1, a1, a2, a3, ...
// pend: b2, b3, b4, ....
static void fj_build_chains(std::vector<int>& v, std::vector<int>& main, std::vector<int>& pend, size_t element_size, size_t count_elements, size_t count_pairs)
{
	// for each pair
	for (size_t pair = 0; pair < count_pairs; pair++)
	{
		size_t start_left = (2 * pair) * element_size;
		size_t start_right = (2 * pair + 1) * element_size;

		// b
		if (pair == 0) // b1 to main chain
			main.insert(main.end(), v.begin() + start_left, v.begin() + start_left + element_size);
		else // other b's in pend chain
			pend.insert(pend.end(), v.begin() + start_left, v.begin() + start_left + element_size);

		// a to main chain
		main.insert(main.end(), v.begin() + start_right, v.begin() + start_right + element_size);
	}
	// add unpaired element to pend
	if (count_elements % 2 == 1)
	{
		size_t start_missing = (count_elements - 1) * element_size;
		pend.insert(pend.end(), v.begin() + start_missing, v.begin() + start_missing + element_size);
	}
}

// STEP 3 - INSERT PEND IN MAIN CHAIN
// respect the border: b2 has to be before a2
static void fj_insert_pend_in_main(std::vector<int>& main, std::vector<int>& pend, size_t element_size, size_t count_elements, size_t count_pairs)
{
	size_t pend_count = pend.size() / element_size;
	if (pend_count > 0)
	{
		std::vector<size_t> insertion_order = get_insertion_order(pend_count);

		// save original position in main for border
		std::vector<size_t> main_positions;
		for (size_t i = 0; i <= count_pairs; i++)
			main_positions.push_back(i); // b1, a1, a2, a3, ...

		// for each pend element
		for (size_t i = 0; i < insertion_order.size(); i++)
		{
			size_t pend_idx = insertion_order[i];

			// get current pend element
			std::vector<int> cur_pend_element(pend.begin() + pend_idx * element_size, pend.begin() + (pend_idx + 1) * element_size);
			int key = cur_pend_element[element_size - 1];

			// claculate border
			// id = (pend[b +2])
			size_t border = main_positions.size(); // whole main chain
			// if odd then search in the whole main chain, because it has no a
			bool is_odd_element = false;
			if ((count_elements % 2 == 1) && (pend_idx == pend_count - 1))
				is_odd_element = true;
			if (!is_odd_element)
			{
				size_t a_element_id = pend_idx + 2;
				// search for index of the a element in main_positions
				for (size_t j = 0; j < main_positions.size(); j++)
				{
					if (main_positions[j] == a_element_id)
					{
						border = j;
						break ;
					}
				}
			}

			// binary search for insert position
			size_t lo = 0;
			size_t hi = border;
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
			// update main chain IDs, insert b[i] with max value
			main_positions.insert(main_positions.begin() + lo, std::numeric_limits<size_t>::max());
		}
	}
}

void fj_algo(std::vector<int> &v, size_t element_size)
{
	if ((v.size() / element_size) < 2)
		return;

	// calculate base params
	size_t count_elements = v.size() / element_size;
	size_t count_pairs = count_elements / 2;

	// step 1
	fj_build_and_sort_pairs(v, count_pairs, element_size);
	fj_algo(v, element_size * 2);

	// init main and pend chain
	std::vector<int> main;
	std::vector<int> pend;
	// step 2
	fj_build_chains(v, main, pend, element_size, count_elements, count_pairs);
	// step 3
	fj_insert_pend_in_main(main, pend, element_size, count_elements, count_pairs);

	// copy sorted main chain back to the original chain
	for (size_t i = 0; i < main.size(); i++)
		v[i] = main[i];

	std::cout << "- after insert ";
	print_vector(v);
}
