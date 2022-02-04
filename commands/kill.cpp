/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:37:18 by nazurmen          #+#    #+#             */
/*   Updated: 2022/02/04 12:07:56 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void	Server::killCmmd(std::vector<std::string>const &tokens, User *usr)
{
	std::string msg;
	User *killed = NULL;

	if (usr->getOper() == false)
		return replyMsg(ERR_NOPRIVILEGES, " :No IRC-Operator privileges", usr);
	if (tokens.size() < 2)
		return replyMsg(ERR_NEEDMOREPARAMS, tokens[0] + " :Not enough parameters", usr);

	std::list<User *>::iterator it;
	for (it = users_on.begin(); it != users_on.end(); it++)
		if (tokens[1].compare((*it)->getNick()) == 0)
			killed = (*it);
	if(!killed)
		return replyMsg(ERR_NOSUCHNICK, tokens[1] + " :Nickname incorrect", usr);
	std::vector<Channel *>::iterator it2;
	for (it2 = killed->getChannels().begin(); killed->getChannels().size() > 0 && it2 != killed->getChannels().end(); ++it2)
	{
		(*it2)->disconnectUser(killed);
		killed->leaveChannel(*it2);
		it2--;
	}
	if (tokens.size() < 3)
		msg += killed->getNickMask() + " KILLED " + " :for controversial reasons";
	else
		msg += killed->getNickMask() + " KILLED :" + tokens[2];  
	send(killed->getFD(), msg.c_str(), msg.length(), 0);
	this->deleteUser(killed);
	return;
}