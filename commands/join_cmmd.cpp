/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:41 by nazurmen          #+#    #+#             */
/*   Updated: 2021/12/11 19:53:59 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

static bool checkIfChannel(const std::string &str)
{
	if (str[0] == '#' || str[0] == '&' || str[0] == '!' || str[0] == '+')
		return true;
	return false;
}

void Server::join_cmd(std::vector<std::string> const &tokens, User* usr)
{
std::cout << "join_cmd\n\n\n\n" << std::endl;
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
				if ((*it)->getName() == tokens[i])
				{
					(*it)->joinUser(usr);
					usr->joinChannel(*it);
					std::cout << "Joined channel " << (*it)->getName() << std::endl;
					std::cout << "Available commands: /msg <user> <message>, /leave, /list, /users, /help" << std::endl;
				}
			}
			try
			{
				Channel* chan = new Channel(usr, tokens[i]);
				this->channels.push_back(chan);
				this->channels.back()->joinUser(usr);
				std::cout << "Joined channel " << this->channels.back()->getName() << std::endl;
				std::cout << "Available commands: /msg <user> <message>, /leave, /list, /users, /help" << std::endl;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				return ;
			}
		}
		else if (checkIfChannel(tokens[i - 1]))
		{
			//key
		}
		else if(tokens[i] == "0")
		{
			std::vector<Channel*>::iterator it;
			for (it = channels.begin(); it != channels.end(); ++it)
			{
				(*it)->disconnectUser(usr);
				usr->leaveChannel(*it);
				std::cout << "Left channel " << (*it)->getName() << std::endl;
			}
		}
		i++;
	}
}
