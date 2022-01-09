/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/09 18:33:06 by javrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "channel.hpp"

void	Server::reply_msg(std::string rep, std::string str, User *usr)
{
    std::string msg;
    
    msg = SERVER_MASK + rep  + " "  + usr->getNick() + " " + str + "\r\n";
	send(usr->getFD(), msg.c_str(), msg.length(), 0);
    // usr->setReply(error);
}

void	Server::msg_to_channel(std::string msg,  User *usr, Channel *chnl)
{
    std::vector<User *>::const_iterator it2;
    std::vector<User *>::const_iterator it3;

    it2 = chnl->getUsers().begin();
    it3 = chnl->getUsers().end();

    for (;it2 != it3; ++it2){
        send((*it2)->getFD(), msg.c_str(), msg.length(), 0);
    }
}
