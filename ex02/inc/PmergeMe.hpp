/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:12:38 by ghambrec          #+#    #+#             */
/*   Updated: 2026/03/10 12:46:50 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <regex>
#include <limits>
#include <algorithm>
#include <chrono>

// ford johnson vector algo
void fjv_algo(std::vector<int>& v, size_t element_size);

// ford johnson deque algo
void fjd_algo(std::deque<int>& d, size_t element_size);
