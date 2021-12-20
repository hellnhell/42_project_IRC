/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/20 18:10:54 by javrodri         ###   ########.fr       */
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

// void	Server::msg_to_user(std::string msg, User *sender_usr, User *recipe_usr)
// {
//     std::string format_message;
    
//     format_message = ":ft_irc.com " + format_message + " "  + recipe_usr->getNick() + "\r\n";
//     send(recipe_usr->getFD(), format_message.c_str(), format_message.length(), 0);
//     // std::cout << error << std::endl;
//     // usr->setReply(error);
// }

//FUTURO MENSAJE DE UN USUARIO A UN CANAL, ITERA POR LOS USUARIOS DENTRO DEL CANAL Y LO ENVIA
//O RECIBE UN VECTOR DE FD Y ENVIA EL MENSAJE A ESOS FDs

void	Server::msg_to_channel(std::string msg, Channel *chnl, User *usr)
{
    std::string     message;
    it_usr_list     beginUsrList = this->users_on.begin();
    it_usr_list     endUsrList = this->users_on.end();

    message.append(usr->getNickMask());
    message.append(" ");
    message.append(msg);
    
    //RECORRER LOS USUARIOS DENNTRO DEL CANAL ENVIANDO EL MENSAJE A CADA UNO DE ELLOS
    
    msg.append("PRIVMSG " + chnl->getName() + " :" + message);
}

