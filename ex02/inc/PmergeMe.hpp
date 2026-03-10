/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:12:38 by ghambrec          #+#    #+#             */
/*   Updated: 2026/03/10 10:30:51 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <regex>
#include <limits>

void print_vector(const std::vector<int>& v);
void fj_algo(std::vector<int>& v, size_t element_size);


// element size 4
// 6 15 8 16 2 11 0 17 9 18 14 19 3 10 1 21 5 12 4 20 7 13
// main: 6 15 8 16 2 11 0 17 3 10 1 21 
// pend: 9 18 14 19 5 12 4 20
// rest: 7 13


// jacobsthal zahlen
// 0, 1, 1, 3, 5, 11, 21, 43