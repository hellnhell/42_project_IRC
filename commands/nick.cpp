/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:15:28 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/01 11:53:55 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../server.hpp"

void Server::nick(std::vector<std::string> const &tokens, User *usr)
{

	std::map<int, User*>::iterator it;

	if (!usr->getConnectionPswd())
		return perror(ERR_NOPASSWD);
	if(tokens.size() != 2)
		return perror("NICK: error: wrong number of parameters\n");
	if(tokens[1] == usr->getNick())
		return perror("NICK: error: same nickname\n");
	if(tokens[1].size() > 9)
		return perror("NICK: error: nick lenght greater than 9\n");
	if(tokens[1][0] == '-' ||
		tokens[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`|^_-{}[]\\") != std::string::npos)
		return perror("NICK: error: Erroneous Nickname\n");

	for(it = this->list_users.begin(); it != this->list_users.end(); it++)
	{
		std::cout << it->first << " fds chekeados" << std::endl;
		if(it->first >= 4) //N: esto es una chapuza por que no se usar mapas y hay mapas con fds < 4 que peta por no inicializarse maybe
		{
			if((*it).second->getNick() == tokens[1])
			{
				std::cout << "Error nickname " << tokens[1] << " isnt valid" << std::endl;
				send(usr->getFD(), "Not a valid nickname\n", 21, 0); //esto no cumple nada pero por ver algo en el cliente
				std::cout << std::endl << "Nick: " << usr->getNick();
				return ;
			}
		}
	}
	usr->setNick(tokens[1]);
	std::cout << std::endl << "Nick: " << usr->getNick();
}