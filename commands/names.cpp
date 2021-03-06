/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:37:10 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/31 14:54:31 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void    Server::namesCmmd(std::vector<std::string> const& tokens, User *usr)
{
	std::vector<std::string>	tok;
	std::istringstream			ss;
	std::string					tmp;
	std::string					msg;
	Channel						*channel;
	int							pos;
	bool						users_no_channel = 0;

	if(tokens.size() == 1)
	{
		std::vector<Channel *>::const_iterator it2;
		std::vector<User *>::const_iterator it3;
		msg = "";
		for (it2 = this->getChannels().begin(); it2 != this->getChannels().end(); it2++)
		{
			msg += " = " + (*it2)->getName() + " ";
			for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
			{
				std::vector<User *>::const_iterator it4;
				for(it4 = (*it2)->getOps().begin(); it4 != (*it2)->getOps().end(); it4++)
				{
					if((*it3)->getNick() == (*it4)->getNick())
						msg += "@";
				}
				msg += (*it3)->getUser() + " ";
			}
			replyMsg(RPL_ENDOFNAMES," " +  (*it2)->getName() + " :End of /NAMES list.", usr);
		}
		std::map<int, User *>::const_iterator it;
		for (it = this->getUsers().begin(); this->getUsers().size() >= 0 && it != this->getUsers().end(); ++it)
		{
			if(it->second->getChannels().size() <= 0)
			{
				if(!users_no_channel)
					users_no_channel = 1;
				msg += it->second->getUser() + " ";
			}
		}
		replyMsg(RPL_NAMREPLY, msg, usr);
	}
	else
	{
		ss.str(tokens[1]);
		while(getline(ss, tmp, ','))
			tok.push_back(tmp);
		for (int i = 0; i < tok.size(); i++)
		{
			std::vector<Channel *>::const_iterator it2;
			std::vector<User *>::const_iterator it3;
			for (it2 = this->getChannels().begin(); it2 != this->getChannels().end(); it2++)
			{
				if(tok[i] == (*it2)->getName())
				{
					msg = " = " + (*it2)->getName() + " ";
					for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
					{
						std::vector<User *>::const_iterator it4;
						for(it4 = (*it2)->getOps().begin(); it4 != (*it2)->getOps().end(); it4++)
						{
							if((*it3)->getNick() == (*it4)->getNick())
								msg += "@";
						}
						msg += (*it3)->getUser() + " ";
					}
					replyMsg(RPL_NAMREPLY, msg, usr);
					replyMsg(RPL_ENDOFNAMES," " +  (*it2)->getName() + " :End of /NAMES list.", usr);
				}
			}
		}
	}
}
