/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:41 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/11 17:40:14 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

static bool checkIfChannel(const std::string &str)
{
	if (str[0] == '#' || str[0] == '&' || str[0] == '!' || str[0] == '+')
		return true;
    return false;
}

void Server::joinCmmd(std::vector<std::string> const &tokens, User* usr)
{
	std::string     msg;

	size_t i = 1;
	if (tokens.size() < 2)
	{
		std::cout << "Usage: /join <channel>" << std::endl;
		return;
	}
	while(i < tokens.size())
	{
		if(checkIfChannel(tokens[i]))
		{
			std::vector<Channel*>::iterator it;
			for (it = channels.begin(); it != channels.end(); ++it)
			{
				if ((*it)->getName() == tokens[i])
				{
					if((*it)->getKey().size())
					{
						return replyMsg(ERR_BADCHANNELKEY, ":Cannot join channel (+k)", usr);
					}
					(*it)->joinUser(usr);
					usr->joinChannel(*it);
					replyMsg(RPL_TOPIC, ":" + (*it)->getTopic(), usr);
                    usr->getChannels().push_back(*it);
					msg = usr->getNickMask() + " JOIN " + (*it)->getName() + "\n";
 					msgToChannel(msg, usr, (*it));
					return ;
				}
			}
			try
			{
				Channel* chan = new Channel(this, usr, tokens[i]);
				this->channels.push_back(chan);
				this->channels.back()->joinUser(usr);
				replyMsg(RPL_TOPIC, ":" + this->channels.back()->getTopic(), usr);
                usr->getChannels().push_back(chan);
				msg = usr->getNickMask() + " JOIN " + chan->getName() + "\n";
 				msgToChannel(msg, usr, chan);;
				return ;
			}
			catch(const std::exception& e)
			{
				//estover
				replyMsg(ERR_UNAVAILRESOURCE, "Error: " + std::string(e.what()), usr);
				//std::cerr << e.what() << '\n';
				return ;
			}
		}
		else if (checkIfChannel(tokens[i - 1]))
		{
			//key
			std::string key = tokens[i];
			std::vector<Channel*>::iterator it;
			for(it = channels.begin(); it != channels.end(); ++it)
			{
				if((*it)->getName() == tokens[i - 1])
				{
					if(key == (*it)->getKey())
					{
						(*it)->joinUser(usr);
						usr->joinChannel(*it);
						replyMsg(RPL_TOPIC, ":" + (*it)->getTopic(), usr);
						//std::cout << "Joined channel " << (*it)->getName() << std::endl;
						//std::cout << "Available commands: /msg <user> <message>, /leave, /list, /users, /help" << std::endl;
						return ;
					}
					else
					{
						return replyMsg(ERR_BADCHANNELKEY, ":Cannot join channel (+k)", usr);
						//std::cout << "Wrong key" << std::endl;
						return ;
					}
				}
			}
		}
		else if(tokens[i] == "0" && !this->channels.empty())
		{
			std::vector<Channel*>::iterator it;
			for (it = this->channels.begin(); it != this->channels.end(); ++it)
			{
				(*it)->disconnectUser(usr);
				usr->leaveChannel(*it);
				//meter aqui part directamente(?)
				std::cout << "Left channel " << (*it)->getName() << std::endl;
			}
		}
		i++;
	}
}
