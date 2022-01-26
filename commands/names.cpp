/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:37:10 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/26 12:11:03 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

 // ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER       RPL_NAMREPLY                    RPL_ENDOFNAMES
void    Server::namesCmmd(std::vector<std::string> const& tokens, User *usr, Server &serv)
{

	std::vector<std::string>	tok;
	std::istringstream          ss;
	std::string                 tmp;
	std::string                 msg;
	Channel						*channel;
	int pos;
	bool						users_no_channel = 0;

	if(tokens[1].find(',') == std::string::npos)
	{
		//channels con contenido
		std::vector<Channel *>::const_iterator it2;
		std::vector<User *>::const_iterator it3;
		msg = "";
		for (it2 = serv.getChannels().begin(); it2 != serv.getChannels().end(); it2++)
		{
			msg += " = " + (*it2)->getName() + " ";
			for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
			{
				// msg += "\nUser: ";
				std::vector<User *>::const_iterator it4;
				for(it4 = (*it2)->getOps().begin(); it4 != (*it2)->getOps().end(); it4++)
				{
					if((*it3)->getNick() == (*it4)->getNick())
						msg += "@";
				}
				msg += (*it3)->getUser() + " ";
			}
		}
		std::map<int, User *>::const_iterator it;
		for (it = serv.getUsers().begin(); serv.getUsers().size() >= 0 && it != serv.getUsers().end(); ++it)
		{
			if(it->second->getChannels().size() <= 0)
			{
				if(!users_no_channel)
				{
					// msg += "\nChannel: *";
					users_no_channel = 1;
				}
				msg += it->second->getUser() + " ";
			}
		}
		replyMsg(RPL_NAMREPLY, msg, usr);
		replyMsg(RPL_ENDOFNAMES, msg, usr);

	}
	else
	{
		ss.str(tokens[1]);
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
					msg = " = " + (*it2)->getName() + " ";
					for(it3 = (*it2)->getUsers().begin(); it3 != (*it2)->getUsers().end(); it3++)
					{
						// msg += "\nUser: ";
						std::vector<User *>::const_iterator it4;
						for(it4 = (*it2)->getOps().begin(); it4 != (*it2)->getOps().end(); it4++)
						{
							if((*it3)->getNick() == (*it4)->getNick())
								msg += "@";
						}
						msg += (*it3)->getUser();
					}
					replyMsg(RPL_NAMREPLY, msg, usr);
	    			replyMsg(RPL_ENDOFNAMES, msg, usr); //?
				}
			}
		}
		// replyMsg(RPL_ENDOFNAMES, "=  End of /NAMES list", usr);
	}
    replyMsg(RPL_ENDOFNAMES, usr->getUser() + " :End of /NAMES list.", usr); //?
}
