/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names_cmmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:30:36 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/13 19:31:19 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void    Server::names_cmmd(std::vector<std::string> const& tokens, User *usr, Server &serv)
{
	std::vector<std::string>	tok;
	std::istringstream          ss(tokens[1]);
	std::string                 tmp;
	std::string                 msg;
	Channel						*channel;
	int pos;
	bool						users_no_channel = 0;

	if(tokens.size() == 1)
	{
		//channels con contenido
		std::vector<Channel *>::const_iterator it2;
		std::vector<User *>::const_iterator it3;
		msg = "";
		for (it2 = serv.getChannels().begin(); it2 != serv.getChannels().end(); it2++)
		{
			msg += "\nChannel: " + (*it2)->getName();
			for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
			{
				msg += "\nUser: " + (*it3)->getUser();
			}
		}
		std::map<int, User *>::const_iterator it;
		for (it = serv.getUsers().begin(); serv.getUsers().size() >= 0 && it != serv.getUsers().end(); ++it)
		{
			if(it->second->getChannels().size() <= 0)
			{
				if(!users_no_channel)
				{
					msg += "\nChannel: *";
					users_no_channel = 1;
				}
				msg += "\nUser: " + it->second->getUser();
			}
		}
		reply_msg(RPL_NAMREPLY, msg, usr);
	}
	else
	{
		while(getline(ss, tmp, ','))
		{
			std::cout << tmp << std::endl;
			tok.push_back(tmp);
		}
		for (int i = 0; i < tok.size(); i++)
		{
			std::vector<Channel *>::const_iterator it2;
			std::vector<User *>::const_iterator it3;
			for (it2 = serv.getChannels().begin(); it2 != serv.getChannels().end(); it2++)
			{
				if(tok[i] == (*it2)->getName())
				{
					msg = "\nChannel: " + (*it2)->getName();
					for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
					{
						msg += "\nUser: " + (*it3)->getUser();
					}
					reply_msg(RPL_NAMREPLY, msg, usr);
				}
			}
		}
	}


}
