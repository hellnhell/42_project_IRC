/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:35:45 by nazurmen          #+#    #+#             */
/*   Updated: 2021/11/26 22:31:34 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

// NICK <nickname>
void Server::nick_cmd(std::vector<std::string> const &tokens, User *usr)
{
    // check valid nick
	std::map<int, User*>::iterator it;

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
