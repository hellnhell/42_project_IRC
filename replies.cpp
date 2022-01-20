/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/20 12:27:25 by javrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "channel.hpp"

void	Server::replyMsg(std::string rep, std::string str, User *usr)
{
	std::string msg;
	//Comprobar q hay mensaje

	// if (rep >= "400")
	// 	msg = RED SERVER_MASK + rep  + " "  + usr->getNick() + " " + str + WHITE "\r\n";
	// else
	// 	msg = GREEN SERVER_MASK + rep  + " "  + usr->getNick() + " " + str + WHITE "\r\n";
	msg  = rep  + " "  + usr->getNick() + " " + str + "\r\n";

	usr->setReply(msg);

	std::vector<User *>::iterator it;
	if ((it = std::find(buff_users.begin(), buff_users.end(), usr)) != buff_users.end())
	{
		perror("Finded");
		return ;
	}
	buff_users.push_back(usr);
	// while (usr->getReply().size() = 0)
	// {

	// }
	// send(usr->getFD(), msg.c_str(), msg.length(), 0);
}

void	Server::msgToChannel(std::string msg,  User *usr, Channel *chnl)
{
	std::vector<User *>::const_iterator it2;
	std::vector<User *>::const_iterator it3;

	it2 = chnl->getUsers().begin();
	it3 = chnl->getUsers().end();

	for (;it2 != it3; ++it2){
		send((*it2)->getFD(), msg.c_str(), msg.length(), 0);
	}
}
