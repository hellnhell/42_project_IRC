/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/18 17:59:34 by javrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "channel.hpp"

bool		Server::isInChannel(User *usr, Channel *chnl){
	std::vector<User *>::const_iterator it2;
	std::vector<User *>::const_iterator it3;
	
	it2 = chnl->getUsers().begin();
	it3 = chnl->getUsers().end();

	for (;it2 != it3; ++it2){
		if ((*it2)->getUser() == (usr->getUser()))
			return (true);
	}
	return (false);
}

void	Server::replyMsg(std::string rep, std::string str, User *usr)
{
	std::string msg;

	if (rep >= "400")
		msg = RED SERVER_MASK + rep  + " "  + usr->getNick() + " " + str + WHITE "\r\n";
	else
		msg = GREEN SERVER_MASK + rep  + " "  + usr->getNick() + " " + str + WHITE "\r\n";
	send(usr->getFD(), msg.c_str(), msg.length(), 0);
	// usr->setReply(error);
}

void	Server::msgToChannel(std::string msg,  User *usr, Channel *chnl)
{
	std::vector<User *>::const_iterator it2;
	std::vector<User *>::const_iterator it3;
	std::string modes;
	
	it2 = chnl->getUsers().begin();
	it3 = chnl->getUsers().end();
	modes = chnl->getModes();

	for (int i = 0; modes.size() < i; i++){
		if (modes[i] == 'n'){				//usar strchr
			if (isInChannel(usr, chnl)){
				for (;it2 != it3; ++it2){
					send((*it2)->getFD(), msg.c_str(), msg.length(), 0);
				}
			}
			else{
				msg = "You can not sent any messages in this channel, you must join in before.";
				send(usr->getFD(), msg.c_str(), msg.length(), 0);
			}
			return;
		} 
	}

	//obtener los modos del canal
	//comprobar el modo n
		//si lo tiene activado, comprobar el usr está dentro de los users del canal

	for (;it2 != it3; ++it2){
		send((*it2)->getFD(), msg.c_str(), msg.length(), 0);
	}
}
