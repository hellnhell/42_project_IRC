/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:38:04 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/21 13:03:39 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void	Server::quitCmmd(std::vector<std::string> const &tokens, User *usr)
{
	std::string msg;

	if (tokens.size() > 1)
		msg = ": QUIT :" + tokens[1] + "\n";
	else
		msg = ": QUIT : see you soon babe ;)\n";
	if(usr->getChannels().size() <= 0)
	{
		std::cout << "User " << usr->getUser() << " is not in any channel" << std::endl;
		replyMsg(ERR_UNKNOWNERROR, msg, usr) ;
	}
	std::vector<Channel *>::const_iterator it;
	for (it = usr->getChannels().begin(); usr->getChannels().size() > 0 && it != usr->getChannels().end(); it++)
	{
		msgToChannel((*it)->getName() + msg, usr, (*it));
		(*it)->disconnectUser(usr);
		usr->leaveChannel(*it);
		it--;
	}
	actionDisplay("Quited : ", "", usr);
	this->deleteUser(usr);
}
