/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_cmmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:09:08 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/11 17:32:04 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void	Server::partCmmd(std::vector<std::string>const &tokens, User *usr)
{
	std::vector<std::string>	tok;
	std::string					tmp;
	std::istringstream			ss;
	std::string					leave_msg;
	std::string::size_type		pos;

	if (tokens.size() == 1 ) //se puede meter el quit
		return this->replyMsg(ERR_NOSUCHCHANNEL, "<empty> :No such channel", usr);

	std::cout << "\n\n\n token1: " << tokens[1] << std::endl;
	if (tokens.size() > 2)
		leave_msg = tokens[2];
	ss.str(tokens[1]);
	while(getline(ss, tmp, ','))
	{
	 	std::cout << tmp << std::endl;
	 	tok.push_back(tmp);
	}
	//print tok content
	for(int i = 0; i < tok.size(); i++)
		std::cout << "tok[" << i << "]: " << tok[i] << std::endl;
	for(int i = 0; i < tok.size(); i++)
	{
		if(usr->getChannels().size() <= 0)
		{
			std::cout << "User " << usr->getUser() << " is not in any channel" << std::endl;
			return ;
		}
		std::vector<Channel *>::const_iterator it;
		for (it = usr->getChannels().begin(); usr->getChannels().size() > 0 && it != usr->getChannels().end(); ++it)
		{
			if ((*it)->getName() == tok[i])
			{
				if (leave_msg.size() > 0)
				{
					leave_msg += usr->getNickMask() + " PART " + (*it)->getName() + "\n";;
					msgToChannel(leave_msg, usr, *it);
					break ;
					//send leve_msg to all users in channel
				}
				else
				{
					leave_msg = usr->getNickMask() + " PART " + (*it)->getName() + "\n";;
					msgToChannel(leave_msg, usr, *it);
					break ;
					// ???? send generic msg to all users in channel
				}
				(*it)->disconnectUser(usr);
				usr->leaveChannel(*it);
				it--;
			}
		}
	}
}
