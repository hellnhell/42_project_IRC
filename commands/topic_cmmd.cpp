/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic_cmmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:40:47 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/10 00:49:33 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::topic_cmmd(std::vector<std::string> const &tokens, User *usr, Server &serv)
{
	std::string msg;
	Channel *channel;

	std::vector<Channel*>::const_iterator it;
	bool is_in_channel = false;
	for (it = usr->getChannels().begin(); it != usr->getChannels().end(); ++it)
	{
		if ((*it)->getName() == tokens[1])
		{
			is_in_channel = true;
			break;
		}
	}
	if (!is_in_channel)
		return reply_msg(ERR_NOTONCHANNEL, tokens[1], usr);

	//chanoppriv needed
	std::vector<User*>::const_iterator it2;
	bool is_op = false;
	for (it2 = (*it)->getOps().begin(); it2 != (*it)->getOps().end(); ++it2)
	{
		if ((*it2)->getNick() == usr->getNick())
		{
			is_op = true;
			break;
		}
	}

	//nochanmodes
	if (!(*it)->getMode('t'))
		return reply_msg(ERR_CHANOPRIVSNEEDED, tokens[1], usr);

	if (tokens.size() == 1)
		reply_msg(ERR_NOTEXTTOSEND, "", usr);
	else if (tokens.size() == 2)
	{
		channel = serv.getChannel(tokens[1]);
		if (channel)
			reply_msg(RPL_TOPIC, channel->getTopic(), usr);
		else
			reply_msg(ERR_NOSUCHCHANNEL, tokens[1], usr);
	}
	else if (tokens.size() == 3)
	{
		channel = serv.getChannel(tokens[1]);
		if (channel != *this->channels.end())
		{
			//if(std::find(usr->getChannels().begin(), usr->getChannels().end(), channel) != usr->getChannels().end())
			if(is_op)
			{
				channel->setTopic(tokens[2]);
				msg = "Topic for channel " + channel->getName() + " is now: " + tokens[2];
				reply_msg(RPL_TOPIC, msg, usr);
			}
			else
				reply_msg(ERR_NOTONCHANNEL, tokens[1], usr);
		}
		else
			reply_msg(ERR_NOSUCHCHANNEL, tokens[1], usr);
	}
}
