/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:35:45 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/02 11:59:56 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::user_cmd(std::vector<std::string> const &tokens, User *usr)
{
	if (!usr->getConnectionPswd())
		return perror(ERR_NOPASSWD);
	if(tokens.size() < 5)
		return perror("USER: error: not enought parameters\n"); //N: cambiar por errn pero no se si son aleatorios o tienen un criterio
	if(usr->getUser()[0])
		return perror("USER: error: user already registered\n");
	if(!isalnum(tokens[1][0]))
		return perror("USER: error: username not valid\n");
	if(!std::isdigit(tokens[2][0])) //E:si es asterisco tiene q ir
		return perror("USER: error: mode not valid\n");

	usr->setUser(tokens[1]);
	usr->setModes(std::stoi(tokens[2]));
	usr->setRealName(tokens[4]);
	this->users_on.push_back(usr);
	std::cout << std::endl << "User:  " << usr->getUser() << "\nmodes:" << usr->getModes() << "\nReal name: " << usr->getRealName() << std::endl;
}