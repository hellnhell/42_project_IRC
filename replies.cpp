/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2022/01/04 16:47:50 by javrodri         ###   ########.fr       */
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

void	Server::msg_to_channel(std::string msg,  User *usr, Channel *chnl)
{
    std::vector<User *>::const_iterator it2;
    std::vector<User *>::const_iterator it3;

    it2 = chnl->getUsers().begin();
    it3 = chnl->getUsers().end();
      
    //RECORRER LOS USUARIOS DENTRO DEL CANAL ENVIANDO EL MENSAJE A CADA UNO DE ELLOS
    
    // message = "PRIVMSG :" + msg;
    // std::cout << message << std::endl;
    // std::cout << chnl->getName() << std::endl;

    for (;it2 != it3; ++it2){
        send((*it2)->getFD(), msg.c_str(), msg.length(), 0);
    }
}
