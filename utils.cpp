/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:04:16 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/31 12:22:12 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	actionDisplay(std::string const &action, std::string const &cmd, User *usr)
{
	std::cout << action.substr(0,25) 
	<< " IP: " <<  usr->getClientAdd()
	<< " Socket: " << usr->getFD()
	<< " " 
	<<  cmd << std::endl;
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

uint64_t	getTime(void)
{
	static struct timeval	st;

	gettimeofday(&st, NULL);
	return ((st.tv_sec * (uint64_t)1000) + (st.tv_usec / 1000));
}

std::string		toUpper(std::string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return (str);
}