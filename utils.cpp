/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:04:16 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/12 02:49:08 by nazurmen         ###   ########.fr       */
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

void displayDev(Server *serv)
{
	std::cout << "Users connected to the server: " << serv->getUsers().size() << "\n";

	std::map<int, User *>::iterator it;
	for (it = serv->getUsers().begin();serv->getUsers().size() != 0 && it != serv->getUsers().end(); it++)
	{
std::cout << "Users connected to the server: " << serv->getUsers().size() << "\n";
		std::cout << "Socket: " << it->first << " IP: " << it->second->getClientAdd() << "User: " << it->second->getUser() << "\n";
	}


	// std::cout << "Channels: " << serv->getChannels().size() << std::endl;
	// std::vector<Channel *>::iterator it2;
	// std::vector<User *>::iterator it3;
	// for (it2 = serv->getChannels().begin(); it2 != serv->getChannels().end(); it2++)
	// {
	// 	std::cout << "Channel: " << (*it2)->getName() << " Users: " << (*it2)->getUsers().size() << std::endl;
	// 	for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
	// 	{
	// 		std::cout << "User: " << (*it3)->getUser() << " IP: " << (*it3)->getClientAdd() << " Socket: " << (*it3)->getFD() << std::endl;
	// 	}
	// }
}
