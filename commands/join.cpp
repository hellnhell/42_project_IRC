/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:43:41 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/28 16:40:49 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
    //  ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
    //        ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
    //        ERR_CHANNELISFULL               ERR_BADCHANMASK
    //        ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
    //        ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
    //       RPL_TOPIC

static bool checkIfChannel(const std::string &str)
{
	if (str[0] == '#' || str[0] == '&' || str[0] == '!' || str[0] == '+')
		return true;
    return false;
}

void Server::joinCmmd(std::vector<std::string> const &tokens, User* usr)
{
	std::string     msg;
	std::stringstream ss(tokens[1]);
	std::string		tmps;
	std::vector<std::string> tokens2;
	bool			finded = 0;

	size_t i = 0;
	if (tokens.size() < 2)  
		return (replyMsg(ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters", usr));
	while(getline(ss, tmps, ','))
		tokens2.push_back(tmps);
	while(i < tokens2.size())
	{
		std::cout << tokens2[i] << std::endl;
		if(checkIfChannel(tokens2[i]))
		{
			std::vector<Channel*>::iterator it;
			for (it = channels.begin(); it != channels.end(); ++it)
			{
				if ((*it)->getName() == tokens2[i])
				{
					if((*it)->getKey().size())
					{
						return replyMsg(ERR_BADCHANNELKEY, ":Cannot join channel (+k)", usr);
					}
					std::vector<User *>::const_iterator it2;
					if ((it2 = std::find((*it)->getBans().begin(), (*it)->getBans().end(), usr)) != (*it)->getBans().end())
						return this->replyMsg(ERR_BANNEDFROMCHAN, (*it)->getName() + " :Cannot join channel (+b)", usr);

					(*it)->joinUser(usr);
					usr->joinChannel(*it);
					dataMsg("JOIN :" + tokens2[i], usr, usr);
					replyMsg(RPL_TOPIC, ":" + (*it)->getTopic(), usr);
					msg = usr->getNickMask() + " JOIN " + (*it)->getName() + "\n";
 					msgToChannel(msg, usr, (*it));
					finded = 1;
					// return ;
				}
			}
			try
			{
				if(!finded)
				{
					Channel* chan = new Channel(this, usr, tokens2[i]);
					this->channels.push_back(chan);
					this->channels.back()->joinUser(usr);
					usr->joinChannel(chan);
					dataMsg("JOIN :" + tokens2[i], usr, usr); //mirar ahora xq imprime dos veces el join
					msg = " JOIN " + chan->getName() + "\n";
					msgToChannel(msg, usr, chan);
					replyMsg(RPL_TOPIC, ":" + this->channels.back()->getTopic(), usr);
					// return ;
				}
			}
			catch(const std::exception& e)
			{
				//estover
				replyMsg(ERR_UNAVAILRESOURCE, "Error: " + std::string(e.what()), usr);
				//std::cerr << e.what() << '\n';
				return ;
			}
		}
		else if (checkIfChannel(tokens2[i - 1]))
		{
			//key
			std::string key = tokens2[i];
			std::vector<Channel*>::iterator it;
			for(it = channels.begin(); it != channels.end(); ++it)
			{
				if((*it)->getName() == tokens2[i - 1])
				{
					if(key == (*it)->getKey())
					{
						(*it)->joinUser(usr);
						usr->joinChannel(*it);
							 replyMsg(RPL_TOPIC, ":" + (*it)->getTopic(), usr);
							std::cout << "Joined channel " << (*it)->getName() << std::endl;
							std::cout << "Available commands: /msg <user> <message>, /leave, /list, /users, /help" << std::endl;
						// return ;
					}
					else
						return replyMsg(ERR_BADCHANNELKEY, ":Cannot join channel (+k)", usr);
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

