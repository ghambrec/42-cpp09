/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:12:36 by ghambrec          #+#    #+#             */
/*   Updated: 2026/03/03 15:33:13 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void fjalgo(std::vector<int>& v, int pair_size)
{
	if ((v.size() / pair_size) < 2)
		return ;

	// step 1
		
	std::cout << "pairsize: " << pair_size << std::endl;
	fjalgo(v, pair_size * 2);
		
}