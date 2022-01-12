/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:37:18 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/12 12:37:19 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void	Server::killCmmd(std::vector<std::string>const &tokens, User *usr)
{
	std::string msg;

	if (usr->getOper() == false)
		return replyMsg(ERR_NOPRIVILEGES, " :No IRC-Operator privileges", usr);
	if (tokens.size() < 3)
		return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + " :Not enough parameters", usr);

	std::list<User *>::iterator it;
	for (it = users_on.begin(); it != users_on.end(); it++)
	{
		if (tokens[1].compare((*it)->getNick()) != 0)
			return replyMsg(ERR_NOSUCHNICK, tokens[1] + " :Nickname incorrect", usr);
		std::vector<Channel *>::iterator it2;
		for (it2 = (*it)->getChannels().begin(); (*it)->getChannels().size() > 0 && it2 != (*it)->getChannels().end(); ++it2)
		{
			(*it2)->disconnectUser(*it);
			(*it)->leaveChannel(*it2);
			it2--;
		}
		if (!tokens[3].empty())
			msg += RED + (*it)->getNickMask() + " KILLED "  + " :for controversial reasons\n" WHITE;
		else
			msg += RED + (*it)->getNickMask() + " KILLED :" + tokens[3] +"\n" WHITE;  //Meter
		send((*it)->getFD(), msg.c_str(), msg.length(), 0);
		this->deleteUser(*it);
		return;
	}
}
