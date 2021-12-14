/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:04:16 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/14 12:08:04 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	actionDisplay(std::string const &action, std::string const &cmd, User *usr)
{
	// timerDisplay();
	std::cout << action.substr(0,25);
	std::cout << " IP: " <<  usr->getClientAdd();
	std::cout << " Socket: " << usr->getFD();
	std::cout << cmd << std::endl;
}

void	timerDisplay()
{
    time_t tzero = time(0);

    tm ltm = *localtime(&tzero);
		std::cout << PINK_B << std::setfill('0') << std::setw(2) << ltm.tm_hour << ":"
		<< PINK_C << std::setw(2) << ltm.tm_min << ":"
		<< PINK<< std::setw(2) << ltm.tm_sec  << " - "
		<< WHITE << std::setfill(' ') << std::setw(5);
}

