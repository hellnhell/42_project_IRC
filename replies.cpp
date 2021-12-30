/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javrodri <javrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:07:11 by emartin-          #+#    #+#             */
/*   Updated: 2021/12/29 20:16:22 by javrodri         ###   ########.fr       */
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
