/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/10 12:23:49 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void	Server::replyMsg(std::string rep, std::string str, User *usr)
{
	std::string msg;
	
	if (rep[0] > 3)
		msg = RED SERVER_MASK + rep  + " "  + usr->getNick() + " " + str + WHITE "\r\n";
	else        
		msg = GREEN SERVER_MASK + rep  + " "  + usr->getNick() + " " + str + WHITE "\r\n";
	send(usr->getFD(), msg.c_str(), msg.length(), 0);
	// usr->setReply(error);
}

void	Server::msgToChannel(std::string msg,  User *usr, Channel *chnl)
{
	std::string     message;
	// it_usr_list_chnl     beginChnlUsrList = chnl->getUsers().begin();
	// it_usr_list_chnl     endChnlUsrList = chnl->getUsers().end();

	std::vector<User *>::const_iterator it2;
	std::vector<User *>::const_iterator it3;

	it2 = chnl->getUsers().begin();
	it3 = chnl->getUsers().end();
	
	// it_user start = chnl->getUsers().begin();
	// it_user end = chnl->getUsers().end();
	
	// std::cout << "AQUII" << std::endl;
	// std::cout << " " << (*beginChnlUsrList)->getFD() << std::endl;

	// message.append(usr->getNickMask());
	// message.append(" ");
	// message.append(msg);
	
	//RECORRER LOS USUARIOS DENNTRO DEL CANAL ENVIANDO EL MENSAJE A CADA UNO DE ELLOS
	
	message = "PRIVMSG :" + msg;
	std::cout << message << std::endl;
	std::cout << chnl->getName() << std::endl;

	// for (;beginChnlUsrList != endChnlUsrList; ++beginChnlUsrList){
	//     send((*beginChnlUsrList)->getFD(), msg.c_str(), msg.length(), 0);
	// }

	for (;it2 != it3; ++it2){
		send((*it2)->getFD(), message.c_str(), message.length(), 0);
	}
}
