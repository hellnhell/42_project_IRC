/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:35:45 by emartin-          #+#    #+#             */
/*   Updated: 2021/11/26 21:47:37 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

//USER <user> <mode> <unused> <realname>
void Server::user_cmd(std::vector<std::string> const &tokens, User *usr)
{
    if (!usr->getConnectionPswd())
        perror(ERR_NOPASSWD);
    usr->setUser(tokens[1]);
    usr->setModes(std::stoi(tokens[2])); //gestionar si no es int
    usr->setRealName(tokens[4]); // es una coma seguido de varios palabros con espacios
    this->users_on.push_back(usr);
	std::cout << std::endl << "User:  " << usr->getUser() << "\nmodes:" << usr->getModes() << "\nReal name: " << usr->getRealName() << std::endl;
}
