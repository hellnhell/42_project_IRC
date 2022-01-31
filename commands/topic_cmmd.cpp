/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic_cmmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:40:47 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/31 13:50:45 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void Server::topicCmmd(std::vector<std::string> const &tokens, User *usr)
{
	std::string msg;
	Channel *channel;

	if(tokens.size() < 2)
		return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + " :Not enough parameters", usr);

	std::vector<Channel*>::const_iterator it;
	bool is_in_channel = false;
	for (it = usr->getChannels().begin(); it != usr->getChannels().end(); ++it)
		if ((*it)->getName() == tokens[1])
		{
			is_in_channel = true;
			break;
		}
	if (!is_in_channel)
		return replyMsg(ERR_NOTONCHANNEL, tokens[1] + " :Is not in channel", usr);

	std::vector<User*>::const_iterator it2;
	bool is_op = false;
	for (it2 = (*it)->getOps().begin(); it2 != (*it)->getOps().end(); ++it2)
		if ((*it2)->getNick() == usr->getNick())
		{
			is_op = true;
			break;
		}
	if (!(*it)->getMode('t'))
		return replyMsg(ERR_CHANOPRIVSNEEDED, tokens[1] + " :Privilage needed", usr);

	if (tokens.size() == 1)
		replyMsg(ERR_NOTEXTTOSEND, "", usr);
	else if (tokens.size() == 2)
	{
		channel = this->getChannel(tokens[1]);
		if (channel)
			replyMsg(RPL_TOPIC,  channel->getTopic() + " TOPIC :", usr);
		else
			replyMsg(ERR_NOSUCHCHANNEL, tokens[1] + ":No such channel", usr);
	}
	else if (tokens.size() == 3)
	{
		channel = this->getChannel(tokens[1]);
		if (channel)
		{
			if(is_op)
			{
				channel->setTopic(tokens[2]);
				std::vector<User *>::const_iterator it;				
				for(it = channel->getUsers().begin(); it != channel->getUsers().end(); it++) 
					dataMsg("TOPIC " +  tokens[1] + " :" + tokens[2], *it, *it);
			}
			else
				replyMsg(ERR_CHANOPRIVSNEEDED, tokens[1] + " :Privilage needed", usr);
		}
		else
			replyMsg(ERR_NOSUCHCHANNEL, tokens[1] + " :No such channel", usr);
	}
}
