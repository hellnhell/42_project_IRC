/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:04:16 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/07 14:11:02 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void display()
{
    time_t tzero = time(0);
    
    tm ltm = *localtime(&tzero);
    std::cout << GREEN"" << std::setfill('0') << "[" << (ltm.tm_year + 1900) << "/"
			  << std::setw(2) << ltm.tm_mon + 1 << "/"
			  << std::setw(2) << ltm.tm_mday << "_"
			  << std::setw(2) << ltm.tm_hour << ":"
			  << std::setw(2) << ltm.tm_min << ":"
			  << std::setw(2) << ltm.tm_sec << "] "WHITE;
    // std::cout << " : " <<  log.substr(0,25);
	// std::cout << " IP: " <<  usr->getIp();
	// std::cout << " Socket: " << usr->getsockfd();
	// std::cout << cmd << std::endl;
}