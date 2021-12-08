/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:41 by nazurmen          #+#    #+#             */
/*   Updated: 2021/12/08 20:51:46 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

static bool checkIfChannel(const std::string &str)
{
	if (str[0] == '#' || str[0] == '&' || str[0] == '!' || str[0] == '+')
		return true;
	return false;
}

void Server::join_cmd(std::vector<std::string> const &tokens, User* usr)
{
	size_t i = 1;
	if (tokens.size() < 2)
	{
		std::cout << "Usage: /join <channel>" << std::endl;
		return;
	}

	//enviar informacion al usuario joineado sobre el canal y sus comandos disponibles
	while(i < tokens.size())
	{
		if(checkIfChannel(tokens[i]))
		{
			std::vector<Channel*>::iterator it;
			for (it = channels.begin(); it != channels.end(); ++it)
			{
				if ((*it)->getName() == tokens[1])
				{
					(*it)->joinUser(usr);
					std::cout << "Joined channel " << (*it)->getName() << std::endl;
					std::cout << "Available commands: /msg <user> <message>, /leave, /list, /users, /help" << std::endl;
					return;
				}
			}

			this->channels.push_back(new Channel(usr, tokens[1]));
			this->channels.back()->joinUser(usr);
			std::cout << "Joined channel " << this->channels.back()->getName() << std::endl;
			std::cout << "Available commands: /msg <user> <message>, /leave, /list, /users, /help" << std::endl;
		}
		else if (checkIfChannel(tokens[i - 1]))
		{
			//key
		}
		else if(tokens[i] == "0")
		{
			//salirse de todos los canales
		}
	}
}
