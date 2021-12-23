/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic_cmmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:40:47 by nazurmen          #+#    #+#             */
/*   Updated: 2021/12/23 17:27:31 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::topic_cmmd(std::vector<std::string> const &tokens, User *usr, Server &serv)
{
	std::string msg;
	Channel *channel;

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
			if(std::find(usr->getChannels().begin(), usr->getChannels().end(), channel) != usr->getChannels().end())
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
