/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/28 16:21:41 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "channel.hpp"

void	Server::replyMsg(std::string rep, std::string str, User *usr)
{
	std::string msg;
	//Comprobar q hay mensaje
	msg += ":ft_irc.com " + rep +  " " + usr->getNick() + str + "\r\n";
	usr->setReply(msg);

	std::vector<User *>::iterator it;
	if ((it = std::find(buff_users.begin(), buff_users.end(), usr)) != buff_users.end())
		return ;
	buff_users.push_back(usr);
}

void	Server::dataMsg(std::string rep, User *usr, User *usr2)
{
    std::string msg;

	msg = usr->getNickMask() + " " + rep + "\r\n";

	usr2->setReply(msg);
	std::vector<User *>::iterator it;
	if ((it = std::find(buff_users.begin(), buff_users.end(), usr2)) != buff_users.end())
	{
		std::cout <<GREEN << usr2->getNickMask()  << WHITE << std::endl;
		return ;
	}
	buff_users.push_back(usr);
}

void	Server::msgToChannel(std::string msg,  User *usr, Channel *chnl)
{
	std::vector<User *>::const_iterator it2;
	std::vector<User *>::const_iterator it3;

	if(!chnl->getNick(usr->getNick()))
		return ;
	it2 = chnl->getUsers().begin();
	it3 = chnl->getUsers().end();

	for (;it2 != it3; ++it2){
		if(*it2 != usr)
			send((*it2)->getFD(), msg.c_str(), msg.length(), 0);
	}
}
