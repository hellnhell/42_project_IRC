/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:38:04 by nazurmen          #+#    #+#             */
/*   Updated: 2022/01/27 14:09:45 by emartin-         ###   ########.fr       */
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
	std::cout << usr->getChannels().size() << std::endl;
	if(usr->getChannels().size() <= 0)
	{
		std::cout << "User " << usr->getUser() << " is not in any channel" << std::endl;
		replyMsg(ERR_UNKNOWNERROR, msg, usr) ;
	}
	std::vector<Channel *>::const_iterator it;
	for (it = usr->getChannels().begin(); usr->getChannels().size() > 0 && it != usr->getChannels().end(); it++)
	{
		// std::cout << "patata" << std::endl;
		msgToChannel((*it)->getName() + msg, usr, (*it));
		(*it)->disconnectUser(usr);
		usr->leaveChannel(*it);
		it--;
	}
	actionDisplay("Quited : ", "", usr);
	this->deleteUser(usr);
}
